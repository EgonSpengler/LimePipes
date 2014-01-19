/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICMODELTEST_H
#define MUSICMODELTEST_H

#include <musicmodel.h>
#include "config.h"

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
    void testSetData();
    void testInsertTuneIntoScore();
    void testAppendTuneToScore();
    void testInsertTuneWithScore();
    void testInsertPartIntoTune();
    void testAppendPartIntoTune();
    void testInsertMeasureIntoPart();
    void testAppendMeasureToPart();
    void testInsertSymbolIntoMeasure();
    void testAppendSymbolToMeasure();
    void testFlags();
    void testCallOfOkToInsertChild();
    void testQAbstractItemModelImplementation();
    void testItemForIndex();
    void testIndexForItem();
    void testClear();
    void testIsScore();
    void testIsTune();
    void testIsSymbol();
    void testSetColumnCount();
    void testRemoveInvalidRows();
    void testRemoveRows();
    void testSave();
    void testXsdFile();
    void checkTestfilesAgainstXsd(); // long lasting
    void testInvalidDocuments();
    void testValidMinimalDocuments();
    void testValidDocumentThreeScores();
    void testInvalidScoreTuneWithNoInstrument();
    void testInvalidScoreWrongItemsUnderScore();
    void testInvalidScoreFourValidTunes();
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
    void testDropMimeDataScores();
    void testDropMimeDataTunes();
    void testDropMimeDataParts();
    void testDropMimeDataMeasures();
    void testDropMimeDataSymbols();
    void testUndoStackInsertScore();
    void testUndoStackAppendScore();
    void testUndoStackInsertTuneIntoScore();
    void testUndoStackAppendTuneToScore();
    void testUndoStackInsertTuneWithScore();
    void testUndoStackInsertPart();
    void testUndoStackInsertSymbol();
    void testUndoStackRemoveRows();
    void testUndoStackDropMimeData();

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

#endif

