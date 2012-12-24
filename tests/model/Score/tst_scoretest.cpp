/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <datatypes/timesignature.h>
#include <itemdatatypes.h>
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
    m_score->setData("test title", LP::scoreTitle);
    QVERIFY2(m_score->data(LP::scoreTitle) == "test title", "Failed set title");

    m_score->setData("test composer", LP::scoreComposer);
    QVERIFY2(m_score->data(LP::scoreComposer) == "test composer", "Failed set composer");

    m_score->setData("test arranger", LP::scoreArranger);
    QVERIFY2(m_score->data(LP::scoreArranger) == "test arranger", "Failed set arranger");

    m_score->setData("test year", LP::scoreYear);
    QVERIFY2(m_score->data(LP::scoreYear) == "test year", "Failed set year");

    m_score->setData("test copyright", LP::scoreCopyright);
    QVERIFY2(m_score->data(LP::scoreCopyright) == "test copyright", "Failed set copyright");

    m_score->setData(QVariant::fromValue(TimeSignature(TimeSignature::_3_4)), LP::scoreTimeSignature);
    QVERIFY2(m_score->data(LP::scoreTimeSignature).value<TimeSignature>().signature() == TimeSignature::_3_4, "Failed set time signature");
}

void ScoreTest::testConstructor()
{
    delete m_score;
    m_score = new Score(QString("The Title"));
    QVERIFY2(m_score->data(LP::scoreTitle) == "The Title", "Failed setting the score title in the constructor");
    QVERIFY2(m_score->type() == MusicItem::ScoreType, "Score returns the wrong type");
    QVERIFY2(m_score->childType() == MusicItem::TuneType, "The child itemtype of score is not TuneType");
}

void ScoreTest::testSetGetTitle()
{
    m_score->setTitle(QString("New Title"));
    QVERIFY2(m_score->data(LP::scoreTitle) == "New Title", "Failed setting title");
    QVERIFY2(m_score->title() == "New Title", "Failed getting title");
}

void ScoreTest::testWriteToXmlStream()
{
    QString data;
    QXmlStreamWriter writer(&data);

    QString scoreTitle("test title");
    QString scoreComposer("test composer");
    QString scoreArranger("test arranger");
    QString scoreYear("test year");
    QString scoreCopyright("test copyright");
    TimeSignature scoreTimeSig(TimeSignature::_3_8);

    m_score->setTitle(scoreTitle);
    m_score->setData(scoreComposer, LP::scoreComposer);
    m_score->setData(scoreArranger, LP::scoreArranger);
    m_score->setData(scoreYear, LP::scoreYear);
    m_score->setData(scoreCopyright, LP::scoreCopyright);
    m_score->setData(QVariant::fromValue<TimeSignature>(scoreTimeSig), LP::scoreTimeSignature);

    m_score->writeItemDataToXmlStream(&writer);

    QVERIFY2(data.contains(patternForTag("TITLE", scoreTitle), Qt::CaseInsensitive), "No title tag found");
    QVERIFY2(data.contains(patternForTag("COMPOSER", scoreComposer), Qt::CaseInsensitive), "No composer tag found");
    QVERIFY2(data.contains(patternForTag("ARRANGER", scoreArranger), Qt::CaseInsensitive), "No arranger tag found");
    QVERIFY2(data.contains(patternForTag("YEAR", scoreYear), Qt::CaseInsensitive), "No year tag found");
    QVERIFY2(data.contains(patternForTag("COPYRIGHT", scoreCopyright), Qt::CaseInsensitive), "No copyright tag found");
    QVERIFY2(data.contains(TimeSignature::xmlTagName(), Qt::CaseInsensitive), "Time signature wasn't written to xml stream");
}

void ScoreTest::testReadFromXmlStream()
{
    readTextElement("TiTlE", "Testtitle");
    QVERIFY2(m_score->title() == "Testtitle", "Failed loading score title with no uppercase tag");

    readTextElement("CoMPOsER", "Test composer");
    QVERIFY2(m_score->data(LP::scoreComposer) == "Test composer", "Failed loading score composer with no uppercase tag");

    readTextElement("ARrANgER", "Test arranger");
    QVERIFY2(m_score->data(LP::scoreArranger) == "Test arranger", "Failed loading score arranger with no uppercase tag");

    readTextElement("YeAr", "Test year");
    QVERIFY2(m_score->data(LP::scoreYear) == "Test year", "Failed loading score year with no uppercase tag");

    readTextElement("CopYRIgHT", "Test copyright");
    QVERIFY2(m_score->data(LP::scoreCopyright) == "Test copyright", "Failed loading score copyright with no uppercase tag");

    TimeSignature::Type timeSig = TimeSignature::_12_8;
    readTimeSignatureElement(timeSig);

    QVERIFY2(m_score->data(LP::scoreTimeSignature).isValid(), "No valid time signature after loading");
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

void ScoreTest::readTimeSignatureElement(TimeSignature::Type type)
{
    TimeSignature timeSig(type);
    QString data;
    QXmlStreamWriter writer(&data);
    timeSig.writeToXmlStream(&writer);

    readString(data);
}

QString ScoreTest::patternForTag(const QString &tagname, const QString &data)
{
    QString tag = QString("<") + tagname + ">" + data;
    return tag;
}

QTEST_APPLESS_MAIN(ScoreTest)

#include "tst_scoretest.moc"
