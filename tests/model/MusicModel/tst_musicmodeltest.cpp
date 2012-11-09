/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QDir>
#include <QSignalSpy>
#include <QMetaType>
#include <QStack>
#include <QTemporaryFile>
#include <QXmlStreamReader>
#include "qt_modeltest/modeltest.h"
#include <musicmodel.h>
#include <utilities/error.h>
#include <itemdatatypes.h>
#include <instrument.h>
#include <symbol.h>
#include <score.h>
#include <tune.h>

Q_IMPORT_PLUGIN(lp_musicmodeltestplugin)

namespace {

const int CompressionLevelOfMimeData = 9;
const QString ScoreMimeType  = "application/vnd.limepipes.xml.score.z";
const QString TuneMimeType   = "application/vnd.limepipes.xml.tune.z";
const QString SymbolMimeType = "application/vnd.limepipes.xml.symbol.z";

}

class MusicModelTest : public QObject
{
    Q_OBJECT

public:
    MusicModelTest()
        : m_model(0)
    { qRegisterMetaType<QModelIndex>("QModelIndex"); }
    
private Q_SLOTS:
    void initTestcase();
    void cleanupTestcase();
    void init();
    void cleanup();
    void testColumnCount();
    void testInsertScore();
    void testAppendScore();
    void testInsertTuneIntoScore();
    void testAppendTuneToScore();
    void testInsertTuneWithScore();
    void testInsertSymbol();
    void testCallOfOkToInsertChild();
    void testQAbstractItemModelImplementation();
    void testItemForIndex();
    void testClear();
    void testIsScore();
    void testIsTune();
    void testIsSymbol();
    void testSetColumnCount();
    void testRemoveRows();
    void testSave();
    void testInvalidDocuments();
    void testValidMinimalDocuments();
    void testValidDocumentThreeScores();
    void testInvalidScores();
    void testValidScoreThreeValidTunes();
    void testInvalidTunes();
    void testInvalidSymbols();
    void testValidTuneThreeValidSymbols();
    void testLoadedInstrument();
    void testLoadedSymbolName();
    void testLoadedSymbolPitch();
    void testSupportedDragAndDropActions();
    void testMimeTypes();
    void testMimeData();

private:
    void checkForTuneCount(const QString &filename, int count);
    void checkForScoreCount(const QString &filename, int count);
    void checkForSymbolCount(const QString &filename, int count);
    void loadModel(const QString &filename);
    void populateModelWithTestdata();
    void checkMimeDataForTags(const QModelIndexList &indexes, const QString &tagName);
    void checkMimeDataForTagname(const QMimeData *data, const QString &tagname);
    void checkRootChildItemsForTagnameAndCount(QXmlStreamReader *reader, const QString &tagName, int count);
    QFileInfoList fileInfosForPatternList(const QStringList &patterns);
    bool isMusicItemTag(const QStringRef &tagName);
    void checkTagHierarchy(const QStringRef &parentTag, const QStringRef &tag);
    MusicModel *m_model;
    QStringList m_instrumentNames;
    QStringList m_symbolNames;
    QStringList m_musicItemTagNames;
};

void MusicModelTest::initTestcase()
{
    m_instrumentNames = m_model->instrumentNames();
    if (m_instrumentNames.isEmpty()) {
        qWarning("There was no plugin loaded by the model.");
        return;
    }

    m_symbolNames = m_model->symbolNamesForInstrument(m_instrumentNames.at(0));
    if (m_symbolNames.isEmpty()) {
        qWarning("Plugin's instrument has no symbols.");
        return;
    }

    m_musicItemTagNames = QStringList() << "SCORE" << "TUNE" << "SYMBOL" << "LIMEPIPES";
}

void MusicModelTest::cleanupTestcase()
{
}

void MusicModelTest::init()
{
    m_model = new MusicModel(this);
}

void MusicModelTest::cleanup()
{
    delete m_model;
}

void MusicModelTest::testColumnCount()
{
    QVERIFY2(m_model->columnCount(QModelIndex()) == 1, "Wrong column count");
}

void MusicModelTest::testInsertScore()
{
    QModelIndex firstScore = m_model->insertScore(0, "First Title");
    QVERIFY2(m_model->rowCount(QModelIndex()) == 1, "Score was not inserted");
    QVERIFY2(firstScore.isValid(), "No valid Modelindex was returned while inserting score");
    QVERIFY2(firstScore.row() == 0, "Score was inserted in wrong row");
    QVERIFY2(firstScore.column() == 0, "Score was inserted in wrong column");
    QVERIFY2(m_model->data(firstScore, LP::scoreTitle) == "First Title", "Failed score title");

    m_model->setData(firstScore, "Score 1", LP::scoreTitle);
    QModelIndex secondScore = m_model->insertScore(m_model->rowCount(QModelIndex()), "Second Title");
    m_model->setData(secondScore, "Score 2", LP::scoreTitle);
    QVERIFY2(secondScore.data(LP::scoreTitle) == "Score 2", "Score 2's title isn't there");
    QVERIFY2(secondScore.row() == m_model->rowCount(QModelIndex()) - 1, "Score 2 was inserted in wrong row");
    QVERIFY2(secondScore.column() == 0, "Score 2 was inserted in wrong column");

    // Now, the rowsInserted signal should not be called when inserting rows
    QSignalSpy spy(m_model, SIGNAL(rowsInserted(const QModelIndex, int, int)));

    m_model->insertScore(-1, "Failed Score1");
    m_model->insertScore(5, "Failed Score2");

    QVERIFY2(spy.count() == 0, "rowsInserted Signal was emitted" );
}

void MusicModelTest::testAppendScore()
{
    QModelIndex firstScore = m_model->appendScore("First title");
    QVERIFY2(firstScore.isValid(), "Failed appending score");
    QVERIFY2(m_model->data(firstScore, LP::scoreTitle) == "First title", "Failed getting title from appended score");
}

void MusicModelTest::testInsertTuneIntoScore()
{
    QModelIndex score = m_model->insertScore(0, "First Score");
    QVERIFY2(score.isValid(), "Failed inserting score");
    QModelIndex tune = m_model->insertTuneIntoScore(0, score, m_instrumentNames.at(0));
    InstrumentPtr instrument = m_model->data(tune, LP::tuneInstrument).value<InstrumentPtr>();

    QVERIFY2(tune.isValid(), "Failed inserting Tune");
    QVERIFY2(instrument->name() == m_instrumentNames.at(0), "Failed getting instrument back");

    // Now, the rowsInserted signal should not be called when inserting rows
    QSignalSpy spy(m_model, SIGNAL(rowsInserted(const QModelIndex, int, int)));

    m_model->insertTuneIntoScore(-1, score, m_instrumentNames.at(0));
    m_model->insertTuneIntoScore(5, score, m_instrumentNames.at(0));

    QVERIFY2(spy.count() == 0, "rowsInserted Signal was emitted" );
}

void MusicModelTest::testAppendTuneToScore()
{
    QModelIndex score = m_model->insertScore(0, "First Score");
    QVERIFY2(score.isValid(), "Failed inserting score");
    QModelIndex tune = m_model->appendTuneToScore(score, m_instrumentNames.at(0));
    InstrumentPtr instrument = m_model->data(tune, LP::tuneInstrument).value<InstrumentPtr>();

    QVERIFY2(tune.isValid(), "Failed inserting Tune");
    QVERIFY2(instrument->name() == m_instrumentNames.at(0), "Failed getting instrument back");
}

void MusicModelTest::testInsertTuneWithScore()
{
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    InstrumentPtr instrument = m_model->data(tune, LP::tuneInstrument).value<InstrumentPtr>();

    QVERIFY2(tune.isValid(), "Failed inserting Tune");
    QVERIFY2(instrument->name() == m_instrumentNames.at(0), "Failed getting score title from index");
    // New tune and new score => tune in row and column 0
    QVERIFY2(tune.column() == 0, "Tune is in wrong column");
    QVERIFY2(tune.row() == 0, "Tune is in wrong row");
}

void MusicModelTest::testInsertSymbol()
{
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex symbol1 = m_model->insertSymbol(0, tune, m_symbolNames.at(0));
    QVERIFY2(symbol1.isValid(), "Failed inserting symbol");

    // Now, the rowsInserted signal should not be called when inserting rows
    QSignalSpy spy(m_model, SIGNAL(rowsInserted(const QModelIndex, int, int)));

    m_model->insertSymbol(5, tune, m_symbolNames.at(0));
    m_model->insertSymbol(-1, tune, m_symbolNames.at(0));

    QVERIFY2(spy.count() == 0, "rowsInserted Signal was emitted" );
}

void MusicModelTest::testCallOfOkToInsertChild()
{
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));

    QModelIndex validSymbol = m_model->insertSymbol(0, tune, m_symbolNames.at(0));
    QVERIFY2(validSymbol.isValid(), "Failed inserting valid symbol");

    QModelIndex invalidSymbol = m_model->insertSymbol(0, tune, "invalid symbol name");
    QVERIFY2(invalidSymbol.isValid() == false, "Failed. It was possible to insert a invalid symbol name");
}

void MusicModelTest::testQAbstractItemModelImplementation()
{
    for (int i=0; i < 3; i++) {
        m_model->insertScore(0, "Score Title");
    }

    QModelIndex secondScore = m_model->index(1, 0, QModelIndex());
    QVERIFY2(secondScore.isValid(), "Failed getting valid score");

    QModelIndex tune1 = m_model->insertTuneIntoScore(0, secondScore, m_instrumentNames.at(0));
    m_model->insertTuneIntoScore(0, secondScore, m_instrumentNames.at(0));

    m_model->insertSymbol(0, tune1, m_symbolNames.at(0));
    m_model->insertSymbol(1, tune1, m_symbolNames.at(0));
    m_model->insertSymbol(2, tune1, m_symbolNames.at(0));
    m_model->insertSymbol(1, tune1, m_symbolNames.at(0));

    ModelTest * modelTest = new ModelTest(m_model, this);
    delete modelTest;
}

void MusicModelTest::testItemForIndex()
{
    QModelIndex scoreIndex = m_model->insertScore(0, "Random Title");
    MusicItem *score = m_model->itemForIndex(scoreIndex);
    QVERIFY2(score->data(LP::scoreTitle) == "Random Title", "Failed to get the correct item for an index");
}

void MusicModelTest::testClear()
{
    m_model->insertScore(0, "Title");
    QVERIFY2(m_model->index(0, 0, QModelIndex()).isValid() == true, "At least one item should be in the model for next test");
    m_model->clear();
    QVERIFY2(m_model->index(0, 0, QModelIndex()).isValid() == false, "Model wasn't cleared");
}

void MusicModelTest::testIsScore()
{
    QModelIndex firstScore = m_model->appendScore("First title");
    QVERIFY2(m_model->isIndexScore(firstScore), "Failed, should return true for score");
}

void MusicModelTest::testIsTune()
{
    QModelIndex score = m_model->insertScore(0, "First Score");
    QModelIndex tune = m_model->appendTuneToScore(score, m_instrumentNames.at(0));
    QVERIFY2(m_model->isIndexTune(tune), "Faile, should return true for tune");
}

void MusicModelTest::testIsSymbol()
{
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex symbol1 = m_model->insertSymbol(0, tune, m_symbolNames.at(0));
    QVERIFY2(m_model->isIndexSymbol(symbol1), "Failed, should return true for symbol");
}

void MusicModelTest::testSetColumnCount()
{
    QVERIFY2(m_model->columnCount(QModelIndex()) == 1, "Default column count wasn't 1");
    m_model->setColumnCount(4);
    QVERIFY2(m_model->columnCount(QModelIndex()) == 4, "Can't set column count");
}

void MusicModelTest::testRemoveRows()
{
    QString symbolNameWithLength = "Testsymbol with pitch and length";
    int indexOfTestsymbol = m_symbolNames.indexOf(symbolNameWithLength);
    Q_ASSERT(indexOfTestsymbol != -1);

    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex symbol1 = m_model->insertSymbol(0, tune, symbolNameWithLength);
    m_model->setData(symbol1, Length::_1, LP::symbolLength);
    QModelIndex symbol2 = m_model->insertSymbol(0, tune, symbolNameWithLength);
    m_model->setData(symbol2, Length::_2, LP::symbolLength);
    QModelIndex symbol3 = m_model->insertSymbol(0, tune, symbolNameWithLength);
    m_model->setData(symbol3, Length::_4, LP::symbolLength);

    Q_ASSERT(m_model->rowCount(tune) == 3);

    QModelIndex thirdSymbol = m_model->index(2, 0, tune);
    Q_ASSERT(thirdSymbol.isValid());
    Length::Value lengthOfThirdSymbol = m_model->data(thirdSymbol, LP::symbolLength).value<Length::Value>();

    QVERIFY2(m_model->removeRows(0, 2, tune), "Remove rows returned false");

    QVERIFY2(m_model->rowCount(tune) == 1, "Wrong row count after removing rows");

    QModelIndex lastRemainingSymbol = m_model->index(0, 0, tune);
    Q_ASSERT(thirdSymbol.isValid());

    Length::Value lengthOfLastRemaining = m_model->data(lastRemainingSymbol, LP::symbolLength).value<Length::Value>();

    QVERIFY2(lengthOfThirdSymbol == lengthOfLastRemaining, "Length value of last remaining symbol is wron");
}

void MusicModelTest::testSave()
{
    QTemporaryFile tempFile;
    QStack<QStringRef> musicItemTagStack;
    Q_ASSERT(tempFile.open());

    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    m_model->insertSymbol(0, tune, m_symbolNames.at(0));
    m_model->insertSymbol(0, tune, m_symbolNames.at(0));
    tune = m_model->insertTuneWithScore(0, "Second Score", m_instrumentNames.at(0));
    m_model->insertSymbol(0, tune, m_symbolNames.at(0));
    m_model->insertSymbol(0, tune, m_symbolNames.at(0));

    m_model->save(tempFile.fileName());

    QXmlStreamReader reader(&tempFile);

    // Check nesting of items
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (isMusicItemTag(reader.name())) {
                if (musicItemTagStack.count())
                    checkTagHierarchy(musicItemTagStack.top(), reader.name());
                musicItemTagStack.push(reader.name());
            }
        }
        if (reader.isEndElement()) {
            if (isMusicItemTag(reader.name())) {
                QVERIFY2(musicItemTagStack.pop() == reader.name(), "Music items are not correctly nested");
            }
        }
    }
    QString errorMessage = QString("Error occured while reading saved xml file: ") + reader.errorString();
    QVERIFY2(!reader.hasError(), errorMessage.toUtf8());

    // Check for instrument and symbol name attribute
    tempFile.reset();
    reader.setDevice(&tempFile);
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == "TUNE") {
                QVERIFY2(reader.attributes().hasAttribute("INSTRUMENT"), "Tune has no instrument attribute");
                QVERIFY2(reader.attributes().value("INSTRUMENT") == m_instrumentNames.at(0), "Tune returned wrong instrument name");
            }
            if (reader.name() == "SYMBOL") {
                QVERIFY2(reader.attributes().hasAttribute("NAME"), "Symbol has no name attribute");
                QVERIFY2(!reader.attributes().value("NAME").isEmpty(), "Symbol name was empty");
            }
        }
        if (reader.isEndElement()) {

        }
    }
    errorMessage = QString("Error occured while reading saved xml file for attribute check: ") + reader.errorString();
    QVERIFY2(!reader.hasError(), errorMessage.toUtf8());
}

bool MusicModelTest::isMusicItemTag(const QStringRef &tagName)
{
    QString tag = QString().append(tagName);
    return m_musicItemTagNames.contains(tag, Qt::CaseInsensitive);
}

void MusicModelTest::checkTagHierarchy(const QStringRef &parentTag, const QStringRef &tag)
{
    QString parentTagStr = QString().append(parentTag);
    QString tagStr = QString().append(tag);

    if (parentTagStr.compare("LIMEPIPES", Qt::CaseInsensitive) == 0) {
        QVERIFY2(tagStr.compare("SCORE", Qt::CaseInsensitive) == 0, "Failed, tag can't be under LIMEPIPES tag");
    }

    if (parentTagStr.compare("SCORE", Qt::CaseInsensitive) == 0) {
        QVERIFY2(tagStr.compare("TUNE", Qt::CaseInsensitive) == 0, "Failed, tag can't be under SCORE tag");
    }

    if (parentTagStr.compare("TUNE", Qt::CaseInsensitive) == 0) {
        QVERIFY2(tagStr.compare("SYMBOL", Qt::CaseInsensitive) == 0, "Failed, tag can't be under TUNE tag");
    }
}

QFileInfoList MusicModelTest::fileInfosForPatternList(const QStringList &patterns)
{
    QDir testFileDir(QString(SRCDIR) + "test_files");
    Q_ASSERT(testFileDir.exists());
    return testFileDir.entryInfoList(patterns, QDir::Files);
}

void MusicModelTest::testInvalidDocuments()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "invalid_document*.lime");

    foreach (QFileInfo file, fileInfos) {
        checkForScoreCount(file.absoluteFilePath(), 0);
    }
}

void MusicModelTest::testValidMinimalDocuments()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "valid_document_minimal*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        checkForScoreCount(file.absoluteFilePath(), 1);
    }
}

void MusicModelTest::testValidDocumentThreeScores()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "valid_document_three_scores*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        checkForScoreCount(file.absoluteFilePath(), 3);
    }
}

void MusicModelTest::checkForScoreCount(const QString &filename, int count)
{
    loadModel(filename);
    int scoreCount = m_model->rowCount(QModelIndex());
    QString message = QString("Wrong count of scores loaded (") + QString::number(scoreCount) + " scores) from file: " + filename;
    QVERIFY2(scoreCount == count, message.toUtf8());
}

void MusicModelTest::testInvalidScores()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "invalid_score*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        checkForTuneCount(file.absoluteFilePath(), 0);
    }
}

void MusicModelTest::testValidScoreThreeValidTunes()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "valid_score_three*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        checkForTuneCount(file.absoluteFilePath(), 3);
    }
}

void MusicModelTest::checkForTuneCount(const QString &filename, int count)
{
    loadModel(filename);
    QModelIndex scoreIndex = m_model->index(0, 0, QModelIndex());

    int tuneCount = 0;
    if (scoreIndex.isValid())
        tuneCount = m_model->rowCount(scoreIndex);

    QString message = QString("Wrong count of scores loaded (" + QString::number(tuneCount) + " tunes) from file: ") + filename;
    QVERIFY2(tuneCount == count, message.toUtf8());
}

void MusicModelTest::loadModel(const QString &filename)
{
    try {
        m_model->load(filename);
    } catch (LP::Error &error) {
        qWarning() << "Error: " << QString::fromUtf8(error.what()) + filename;
    }
}

void MusicModelTest::testInvalidTunes()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "invalid_tune*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        checkForSymbolCount(file.absoluteFilePath(), 0);
    }
}

void MusicModelTest::testValidTuneThreeValidSymbols()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "valid_tune_three*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        checkForSymbolCount(file.absoluteFilePath(), 3);
    }
}

void MusicModelTest::testLoadedInstrument()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "valid_tune_test_loaded_instrument*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        loadModel(file.absoluteFilePath());

        QModelIndex scoreIndex = m_model->index(0, 0, QModelIndex());
        QModelIndex tuneIndex = m_model->index(0, 0, scoreIndex);

        QVERIFY2(scoreIndex.isValid() && tuneIndex.isValid(), "No valid indexes");

        QVariant instrumentVar = tuneIndex.data(LP::tuneInstrument);
        QVERIFY2(instrumentVar.isValid(), "No valid instrument");
        QVERIFY2(instrumentVar.canConvert<InstrumentPtr>(), "Can't convert into instrument");

        InstrumentPtr instrument = instrumentVar.value<InstrumentPtr>();
        QVERIFY2(instrument->name() == m_instrumentNames.at(0), "Valid instrument wasn't loaded");
    }
}

void MusicModelTest::testLoadedSymbolName()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "valid_symbol_*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        loadModel(file.absoluteFilePath());

        QModelIndex scoreIndex = m_model->index(0, 0, QModelIndex());
        QModelIndex tuneIndex = m_model->index(0, 0, scoreIndex);
        QModelIndex symbolIndex = m_model->index(0, 0, tuneIndex);

        QVERIFY2(scoreIndex.isValid() &&
                 tuneIndex.isValid() &&
                 symbolIndex.isValid(), "No valid indexes");

        QVariant symbolNameVar = symbolIndex.data(LP::symbolName);
        QVERIFY2(symbolNameVar.isValid(), "No valid symbol name");
        QVERIFY2(!symbolNameVar.toString().isEmpty(), "Symbol name is empty or invalid");

        QString symbolName = symbolNameVar.toString();
        QVERIFY2(symbolName == m_symbolNames.at(0), "Symbol name doesn't match");
    }
}

void MusicModelTest::testLoadedSymbolPitch()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "valid_symbolpitch*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        loadModel(file.absoluteFilePath());

        QModelIndex scoreIndex = m_model->index(0, 0, QModelIndex());
        QModelIndex tuneIndex = m_model->index(0, 0, scoreIndex);
        QModelIndex symbolIndex = m_model->index(0, 0, tuneIndex);

        Q_ASSERT(scoreIndex.isValid() &&
                 tuneIndex.isValid() &&
                 symbolIndex.isValid());

        QVariant symbolPitchVar = symbolIndex.data(LP::symbolPitch);
        Q_ASSERT(symbolPitchVar.isValid());
        Q_ASSERT(symbolPitchVar.canConvert<PitchPtr>());

        PitchPtr pitch = symbolPitchVar.value<PitchPtr>();

        QVERIFY2(pitch->name() == "Low A", "Failed loading Pitch");
    }
}

void MusicModelTest::testSupportedDragAndDropActions()
{
    QVERIFY2(m_model->supportedDragActions() == Qt::MoveAction, "Model doesn't support move drag action");
    QVERIFY2(m_model->supportedDropActions() == Qt::MoveAction, "Model doesn't support move drop action");
}

void MusicModelTest::testMimeTypes()
{
    QVERIFY2(m_model->mimeTypes().contains(ScoreMimeType), "Mime types doesn't contain score type");
    QVERIFY2(m_model->mimeTypes().contains(TuneMimeType), "Mime types doesn't contain tune type");
    QVERIFY2(m_model->mimeTypes().contains(SymbolMimeType), "Mime types doesn't contain symbol type");
}

void MusicModelTest::testMimeData()
{
    populateModelWithTestdata();
    QModelIndex scoreIndex1 = m_model->index(0, 0, QModelIndex());
    Q_ASSERT(scoreIndex1.isValid());
    QModelIndex scoreIndex2 = m_model->index(1, 0, QModelIndex());
    Q_ASSERT(scoreIndex2.isValid());

    QModelIndex tuneIndex1 = m_model->index(0, 0, scoreIndex1);
    Q_ASSERT(tuneIndex1.isValid());
    QModelIndex tuneIndex2 = m_model->index(0, 0, scoreIndex2);
    Q_ASSERT(tuneIndex2.isValid());

    QModelIndex symbolIndex1 = m_model->index(0, 0, tuneIndex1);
    Q_ASSERT(symbolIndex1.isValid());
    QModelIndex symbolIndex2 = m_model->index(1, 0, tuneIndex1);
    Q_ASSERT(symbolIndex2.isValid());

    QModelIndexList indexList = QModelIndexList() << tuneIndex1 << scoreIndex1;
    QVERIFY2(m_model->mimeData(indexList) == 0, "Model should always return 0 if model indexes are from different hierarchy");

    indexList.clear();
    indexList << symbolIndex1 << symbolIndex2;
    QVERIFY2(m_model->mimeData(indexList) != 0, "Model should return non 0 value if indexes are the same hierarchy");

    indexList.clear();
    indexList << scoreIndex1 << scoreIndex2;
    checkMimeDataForTags(indexList, "SCORE");

    indexList.clear();
    indexList << tuneIndex1 << tuneIndex2;
    checkMimeDataForTags(indexList, "TUNE");

    indexList.clear();
    indexList << symbolIndex1 << symbolIndex2;
    checkMimeDataForTags(indexList, "SYMBOL");
}

void MusicModelTest::populateModelWithTestdata()
{
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    m_model->insertSymbol(0, tune, m_symbolNames.at(0));
    m_model->insertSymbol(0, tune, m_symbolNames.at(1));
    tune = m_model->insertTuneWithScore(0, "Second Score", m_instrumentNames.at(0));
    m_model->insertSymbol(0, tune, m_symbolNames.at(1));
    m_model->insertSymbol(0, tune, m_symbolNames.at(0));
}

void MusicModelTest::checkMimeDataForTags(const QModelIndexList &indexes, const QString &tagName)
{
    QMimeData *mimeData = m_model->mimeData(indexes);
    checkMimeDataForTagname(mimeData, tagName);

    QVERIFY2(mimeData->formats().count() == 1, "More than one format is supported by data");
    const QString dataFormat = mimeData->formats().at(0);

    QByteArray xmlData = qUncompress(mimeData->data(dataFormat));
    Q_ASSERT(!xmlData.isEmpty());

    QXmlStreamReader reader(xmlData);
    checkRootChildItemsForTagnameAndCount(&reader, tagName, indexes.count());
}

void MusicModelTest::checkMimeDataForTagname(const QMimeData *data, const QString &tagname)
{
    if (tagname.compare("SCORE", Qt::CaseInsensitive) == 0) {
        QVERIFY2(data->hasFormat(ScoreMimeType), "Mime data has no score format");
        return;
    }
    else if (tagname.compare("TUNE", Qt::CaseInsensitive) == 0) {
        QVERIFY2(data->hasFormat(TuneMimeType), "Mime data has no tune format");
        return;
    }
    else if (tagname.compare("SYMBOL", Qt::CaseInsensitive) == 0) {
        QVERIFY2(data->hasFormat(SymbolMimeType), "Mime data has no symbol format");
        return;
    }
    else {
        Q_ASSERT(true);
    }
}

void MusicModelTest::checkRootChildItemsForTagnameAndCount(QXmlStreamReader *reader, const QString &tagName, int count)
{
    QStack<QString> tagNameStack;

    int countOfXmlRootChildTags = 0;
    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement()) {
            if (tagNameStack.count() == 1) { // Root child
                if (tagName.compare(reader->name(), Qt::CaseInsensitive) == 0) {
                    countOfXmlRootChildTags++;
                } else {
                    Q_ASSERT(true);
                }
            }
            tagNameStack.push(QString().append(reader->name()));
        }
        if (reader->isEndElement()) {
            bool tagNameIsTopOfStack = tagNameStack.top().compare(reader->name(), Qt::CaseInsensitive) == 0;

            QVERIFY2(tagNameIsTopOfStack, "No valid xml");
            Q_ASSERT(tagNameIsTopOfStack);

            if (tagNameIsTopOfStack) {
                tagNameStack.pop();
            }
        }
    }

    QString errorMessage = reader->errorString();
    QVERIFY2(!reader->hasError(), errorMessage.toUtf8());

    QVERIFY2(count == countOfXmlRootChildTags, "Wrong count of root items in mime data");
}

void MusicModelTest::testInvalidSymbols()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "invalid_symbol*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        checkForSymbolCount(file.absoluteFilePath(), 0);
    }
}

void MusicModelTest::checkForSymbolCount(const QString &filename, int count)
{
    loadModel(filename);
    QModelIndex scoreIndex = m_model->index(0, 0, QModelIndex());
    QModelIndex tuneIndex = m_model->index(0, 0, scoreIndex);

    int symbolCount = 0;
    if (scoreIndex.isValid() && tuneIndex.isValid())
        symbolCount = m_model->rowCount(tuneIndex);

    QString message = QString("Wrong count of symbols loaded (" + QString::number(symbolCount) + " symbols) from file: ") + filename;
    QVERIFY2(symbolCount == count, message.toUtf8());
}

QTEST_MAIN(MusicModelTest)

#include "tst_musicmodeltest.moc"
