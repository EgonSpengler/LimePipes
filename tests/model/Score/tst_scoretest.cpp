/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <common/datatypes/timesignature.h>
#include <common/itemdataroles.h>
#include "tst_scoretest.h"

void ScoreTest::init()
{
    m_score = new Score();
}

void ScoreTest::cleanup()
{
    delete m_score;
}

void ScoreTest::testType()
{
    QVERIFY2( m_score->type() == MusicItem::ScoreType, "Score returns the wrong type");
}

void ScoreTest::testChildType()
{
    QVERIFY2(m_score->childType() == MusicItem::TuneType, "The child itemtype of score is not TuneType");
}

void ScoreTest::testSetData()
{
    m_score->setData("test title", LP::ScoreTitle);
    QVERIFY2(m_score->data(LP::ScoreTitle) == "test title", "Failed set title");

    m_score->setData("test type", LP::ScoreType);
    QVERIFY2(m_score->data(LP::ScoreType) == "test type", "Failed set type");

    m_score->setData("test composer", LP::ScoreComposer);
    QVERIFY2(m_score->data(LP::ScoreComposer) == "test composer", "Failed set composer");

    m_score->setData("test arranger", LP::ScoreArranger);
    QVERIFY2(m_score->data(LP::ScoreArranger) == "test arranger", "Failed set arranger");

    m_score->setData("test year", LP::ScoreYear);
    QVERIFY2(m_score->data(LP::ScoreYear) == "test year", "Failed set year");

    m_score->setData("test copyright", LP::ScoreCopyright);
    QVERIFY2(m_score->data(LP::ScoreCopyright) == "test copyright", "Failed set copyright");
}

void ScoreTest::testConstructor()
{
    delete m_score;
    m_score = new Score(QString("The Title"));
    QVERIFY2(m_score->data(LP::ScoreTitle) == "The Title", "Failed setting the score title in the constructor");
    QVERIFY2(m_score->type() == MusicItem::ScoreType, "Score returns the wrong type");
    QVERIFY2(m_score->childType() == MusicItem::TuneType, "The child itemtype of score is not TuneType");
}

void ScoreTest::testSetGetTitle()
{
    m_score->setTitle(QString("New Title"));
    QVERIFY2(m_score->data(LP::ScoreTitle) == "New Title", "Failed setting title");
    QVERIFY2(m_score->title() == "New Title", "Failed getting title");
}

void ScoreTest::testWriteToXmlStream()
{
    QString data;
    QXmlStreamWriter writer(&data);

    QString scoreTitle("test title");
    QString scoreType("test type");
    QString scoreComposer("test composer");
    QString scoreArranger("test arranger");
    QString scoreYear("test year");
    QString scoreCopyright("test copyright");

    m_score->setTitle(scoreTitle);
    m_score->setData(scoreType, LP::ScoreType);
    m_score->setData(scoreComposer, LP::ScoreComposer);
    m_score->setData(scoreArranger, LP::ScoreArranger);
    m_score->setData(scoreYear, LP::ScoreYear);
    m_score->setData(scoreCopyright, LP::ScoreCopyright);

    m_score->writeItemDataToXmlStream(&writer);

    QVERIFY2(data.contains(patternForTag("TITLE", scoreTitle), Qt::CaseInsensitive), "No title tag found");
    QVERIFY2(data.contains(patternForTag("TYPE", scoreType), Qt::CaseInsensitive), "No type tag found");
    QVERIFY2(data.contains(patternForTag("COMPOSER", scoreComposer), Qt::CaseInsensitive), "No composer tag found");
    QVERIFY2(data.contains(patternForTag("ARRANGER", scoreArranger), Qt::CaseInsensitive), "No arranger tag found");
    QVERIFY2(data.contains(patternForTag("YEAR", scoreYear), Qt::CaseInsensitive), "No year tag found");
    QVERIFY2(data.contains(patternForTag("COPYRIGHT", scoreCopyright), Qt::CaseInsensitive), "No copyright tag found");
}

void ScoreTest::testReadFromXmlStream()
{
    readTextElement("TiTlE", "Testtitle");
    QVERIFY2(m_score->title() == "Testtitle", "Failed loading score title with no uppercase tag");

    readTextElement("TyPE", "Testtype");
    QVERIFY2(m_score->data(LP::ScoreType) == "Testtype", "Failed loading score type with no uppercase tag");

    readTextElement("CoMPOsER", "Test composer");
    QVERIFY2(m_score->data(LP::ScoreComposer) == "Test composer", "Failed loading score composer with no uppercase tag");

    readTextElement("ARrANgER", "Test arranger");
    QVERIFY2(m_score->data(LP::ScoreArranger) == "Test arranger", "Failed loading score arranger with no uppercase tag");

    readTextElement("YeAr", "Test year");
    QVERIFY2(m_score->data(LP::ScoreYear) == "Test year", "Failed loading score year with no uppercase tag");

    readTextElement("CopYRIgHT", "Test copyright");
    QVERIFY2(m_score->data(LP::ScoreCopyright) == "Test copyright", "Failed loading score copyright with no uppercase tag");
}

void ScoreTest::readTextElement(const QString &tagName, const QString &elementText)
{
    QString data = QString("<") + tagName + ">" + elementText + "</" + tagName +">";
    readString(data);
}

void ScoreTest::readString(const QString &string)
{
    QXmlStreamReader reader(string);

    QVERIFY2(!reader.atEnd(), "Reader already at end");
    QVERIFY2(!reader.hasError(), "Reader has error");

    while (reader.name().isEmpty()) {
        reader.readNext();
        if (reader.hasError())
            break;
    }

    QVERIFY2(reader.isStartElement(), "No start element given");

    m_score->readCurrentElementFromXmlStream(&reader);

    QVERIFY2(!reader.hasError(), "Reader has error after loading");
}

QString ScoreTest::patternForTag(const QString &tagname, const QString &data)
{
    QString tag = QString("<") + tagname + ">" + data;
    return tag;
}

QTEST_APPLESS_MAIN(ScoreTest)

#include "tst_scoretest.moc"
