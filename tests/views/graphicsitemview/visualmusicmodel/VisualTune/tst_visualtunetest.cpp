/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <views/graphicsitemview/visualmusicmodel/visualtune.h>

class VisualTuneTest : public QObject
{
    Q_OBJECT

public:
    VisualTuneTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testType();

private:
    VisualTune *m_visualTune;
};

VisualTuneTest::VisualTuneTest()
    : m_visualTune(0)
{
}

void VisualTuneTest::init()
{
    m_visualTune = new VisualTune();
}

void VisualTuneTest::cleanup()
{
    delete m_visualTune;
}

void VisualTuneTest::testType()
{
    QVERIFY2(m_visualTune->itemType() == VisualItem::VisualTuneItem,
             "Visual tune returned wrong type");
}

QTEST_APPLESS_MAIN(VisualTuneTest)

#include "tst_visualtunetest.moc"
