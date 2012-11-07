/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <melodynote.h>

class MelodyNoteTest : public QObject
{
    Q_OBJECT

public:
    MelodyNoteTest()
        : m_melody(0) {}

private Q_SLOTS:
    void init();
    void cleanup();
    void testDefaultConstructor();
    void testTypeAndNameConstructor();
    void testDots();
    void testWriteItemDataToStream();
    void testReadFromXmlStream();

private:
    void readTextElement(const QString &tagName, const QString &elementText);
    void readString(const QString &string);
    QString patternForTag(const QString &tagname, const QString &data);
    MelodyNote *m_melody;
};

void MelodyNoteTest::init()
{
    m_melody = new MelodyNote();
}

void MelodyNoteTest::cleanup()
{
    delete m_melody;
}

void MelodyNoteTest::testDefaultConstructor()
{
    QVERIFY2(m_melody->symbolType() == LP::MelodyNote, "Melody Note doesn't return right symbol type in default constructor");
    QVERIFY2(m_melody->data(LP::symbolName) == "Melody Note", "MelodyNote doesn't return symbol name data in default constructor");
    QVERIFY2(m_melody->hasPitch(), "Melody note has no pitch");
    QVERIFY2(m_melody->hasLength(), "Melody note has no length");
    QVERIFY2(m_melody->hasGraphic(), "Melody note has no graphic");
    QVERIFY2(m_melody->data(LP::melodyNoteDots).isValid(), "No default value for dots");
}

void MelodyNoteTest::testTypeAndNameConstructor()
{
    delete m_melody;
    m_melody = new MelodyNote(LP::Bar, "testtest");

    QVERIFY2(m_melody->symbolType() == LP::Bar, "Melody Note doesn't return right symbol type if set through constructor");
    QVERIFY2(m_melody->data(LP::symbolName) == "testtest", "MelodyNote doesn't return symbol name data if set through constructor");
    QVERIFY2(m_melody->hasPitch(), "Melody note has no pitch");
    QVERIFY2(m_melody->hasLength(), "Melody note has no length");
    QVERIFY2(m_melody->hasGraphic(), "Melody note has no graphic");
}

void MelodyNoteTest::testDots()
{
    QVERIFY2(m_melody->itemSupportsWritingOfData(LP::melodyNoteDots), "Melody note doesn't support writing of Dots data");

    m_melody->setData(1, LP::melodyNoteDots);
    QVERIFY2(m_melody->data(LP::melodyNoteDots) == 1, "Failed setting dots");

    m_melody->setData(MelodyNote::MaxDots, LP::melodyNoteDots);
    QVERIFY2(m_melody->data(LP::melodyNoteDots) == MelodyNote::MaxDots, "Failed setting maximum dots");

    m_melody->setData(-1, LP::melodyNoteDots);
    QVERIFY2(m_melody->data(LP::melodyNoteDots) == 0, "Setting less than zero dots should result in zero dots");

    m_melody->setData(MelodyNote::MaxDots + 1, LP::melodyNoteDots);
    QVERIFY2(m_melody->data(LP::melodyNoteDots) == MelodyNote::MaxDots, "Setting more than maximum of dots doesn't result in maximum");
}

void MelodyNoteTest::testWriteItemDataToStream()
{
    QString data;
    QXmlStreamWriter writer(&data);
    PitchPtr testPitch(new Pitch(2, "test pitch name"));
    int dotCnt = 3;

    m_melody->setData(QVariant::fromValue<PitchPtr>(testPitch), LP::symbolPitch);
    m_melody->setData(dotCnt, LP::melodyNoteDots);

    m_melody->writeItemDataToXmlStream(&writer);

    QString pitchTag = patternForTag("PITCH", testPitch->name());
    QString dotsTag = patternForTag("DOTS", QString::number(dotCnt, 10));

    QVERIFY2(data.contains(pitchTag, Qt::CaseInsensitive), "No symbol pitch tag found, maybe the same base class method wasn't called");
    QVERIFY2(data.contains(dotsTag, Qt::CaseInsensitive), "No melody dots tag found");
}

void MelodyNoteTest::testReadFromXmlStream()
{
    int dots = 2;
    Q_ASSERT(dots != m_melody->data(LP::melodyNoteDots).toInt());

    readTextElement("DOTS", QString::number(dots));
    QVERIFY2(m_melody->data(LP::melodyNoteDots).toInt() == dots, "Failed reading dots");

    Length::Value length = Length::_64;
    Q_ASSERT(length != m_melody->length());

    readTextElement("LENGTH", QString::number(length));
    QVERIFY2(m_melody->length() == length, "Failed reading length");
}

QString MelodyNoteTest::patternForTag(const QString &tagname, const QString &data)
{
    QString tag = QString("<") + tagname + ">" + data;
    return tag;
}

void MelodyNoteTest::readTextElement(const QString &tagName, const QString &elementText)
{
    QString data = QString("<") + tagName + ">" + elementText + "</" + tagName +">";
    readString(data);
}

void MelodyNoteTest::readString(const QString &string)
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

    m_melody->readCurrentElementFromXmlStream(&reader);

    QVERIFY2(!reader.hasError(), "Reader has error after loading");
}

QTEST_MAIN(MelodyNoteTest)

#include "tst_melodynotetest.moc"
