/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <timesignature.h>

class TimeSignatureTest : public QObject
{
    Q_OBJECT
    
public:
    TimeSignatureTest();
    
private Q_SLOTS:
    void testBeatCount();
    void testBeatUnit();
    void testQVariant();
    void testWriteToXmlStream();
};

TimeSignatureTest::TimeSignatureTest()
{
}

void TimeSignatureTest::testBeatCount()
{
    QVERIFY2(TimeSignature::beatCount(TimeSignature::_2_2) == 2, "Fail for 2/2");
    QVERIFY2(TimeSignature::beatCount(TimeSignature::_2_4) == 2, "Fail for 2/4");
    QVERIFY2(TimeSignature::beatCount(TimeSignature::_3_4) == 3, "Fail for 3/4");
    QVERIFY2(TimeSignature::beatCount(TimeSignature::_4_4) == 4, "Fail for 4/4");
    QVERIFY2(TimeSignature::beatCount(TimeSignature::_3_8) == 3, "Fail for 3/8");
    QVERIFY2(TimeSignature::beatCount(TimeSignature::_6_8) == 6, "Fail for 6/8");
    QVERIFY2(TimeSignature::beatCount(TimeSignature::_9_8) == 9, "Fail for 9/8");
    QVERIFY2(TimeSignature::beatCount(TimeSignature::_12_8) == 12, "Fail for 12/8");
}

void TimeSignatureTest::testBeatUnit()
{
    QVERIFY2(TimeSignature::beatUnit(TimeSignature::_2_2) == 2, "Fail for 2/2");
    QVERIFY2(TimeSignature::beatUnit(TimeSignature::_2_4) == 4, "Fail for 2/4");
    QVERIFY2(TimeSignature::beatUnit(TimeSignature::_3_4) == 4, "Fail for 3/4");
    QVERIFY2(TimeSignature::beatUnit(TimeSignature::_4_4) == 4, "Fail for 4/4");
    QVERIFY2(TimeSignature::beatUnit(TimeSignature::_3_8) == 8, "Fail for 3/8");
    QVERIFY2(TimeSignature::beatUnit(TimeSignature::_6_8) == 8, "Fail for 6/8");
    QVERIFY2(TimeSignature::beatUnit(TimeSignature::_9_8) == 8, "Fail for 9/8");
    QVERIFY2(TimeSignature::beatUnit(TimeSignature::_12_8) == 8, "Fail for 12/8");
}

void TimeSignatureTest::testQVariant()
{
    QVariant var = QVariant::fromValue(TimeSignature());
    QVERIFY2(var.isValid(), "Failed setting TimeSignature as QVariant");
}

void TimeSignatureTest::testWriteToXmlStream()
{
    QString data;
    QXmlStreamWriter writer(&data);
    TimeSignature timeSig(TimeSignature::_6_8);

    QVERIFY2(!TimeSignature::xmlTagName().isEmpty(), "Time Signature has no xml tag");

    QString timeSigStartTag = QString("<") + TimeSignature::xmlTagName() + ">";
    QString timeSigEndTag = QString("</") + TimeSignature::xmlTagName() + ">";
    QString beatCountTag = QString("<BEATCOUNT>") + QString::number(TimeSignature::beatCount(timeSig.signature()), 10);
    QString beatUnitTag = QString("<BEATUNIT>") + QString::number(TimeSignature::beatUnit(timeSig.signature()), 10);

    timeSig.writeToXmlStream(&writer);

    QVERIFY2(data.contains(timeSigStartTag, Qt::CaseInsensitive), "No time sig start tag found");
    QVERIFY2(data.contains(timeSigEndTag, Qt::CaseInsensitive), "No time sig end tag found");
    QVERIFY2(!data.contains(timeSigStartTag + timeSigEndTag, Qt::CaseInsensitive), "time sig end tag follows directly a start tag");
    QVERIFY2(data.contains(beatCountTag, Qt::CaseInsensitive), "No tag for beat count found");
    QVERIFY2(data.contains(beatUnitTag, Qt::CaseInsensitive), "No tag for beat unit found");
}

QTEST_APPLESS_MAIN(TimeSignatureTest)

#include "tst_timesignaturetest.moc"
