/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <views/graphicsitemview/visualmusicmodel/visualpart.h>

class VisualPartTest : public QObject
{
    Q_OBJECT

public:
    VisualPartTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testType();

private:
    VisualPart *m_visualPart;
};

VisualPartTest::VisualPartTest()
    : m_visualPart(0)
{
}

void VisualPartTest::init()
{
    m_visualPart = new VisualPart();
}

void VisualPartTest::cleanup()
{
    delete m_visualPart;
}

void VisualPartTest::testType()
{
    QVERIFY2(m_visualPart->itemType() == VisualItem::VisualPartItem,
             "Visual part returned wrong type");
}

QTEST_APPLESS_MAIN(VisualPartTest)

#include "tst_visualparttest.moc"
