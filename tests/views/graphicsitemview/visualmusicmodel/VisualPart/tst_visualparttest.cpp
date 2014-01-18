/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <views/graphicsitemview/visualmusicmodel/visualpart.h>

class VisualPartTest : public QObject
{
    Q_OBJECT

public:
    VisualPartTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testConstructor();

private:
    VisualPart *m_visualPart;
};

VisualPartTest::VisualPartTest()
{
}

void VisualPartTest::init()
{
    m_visualPart = new VisualPart;
}

void VisualPartTest::cleanup()
{
    delete m_visualPart;
}

void VisualPartTest::testConstructor()
{
    QVERIFY2(m_visualPart->itemType() == VisualItem::VisualPartItem,
             "Wrong item type returned");
    QVERIFY2(m_visualPart->graphicalType() == VisualItem::GraphicalRowType,
             "Wrong graphical type returned");
}

QTEST_MAIN(VisualPartTest)

#include "tst_visualparttest.moc"
