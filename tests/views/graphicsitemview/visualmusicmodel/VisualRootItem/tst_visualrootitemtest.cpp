/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <views/graphicsitemview/visualmusicmodel/visualrootitem.h>
#include <QtTest/QtTest>
#include <QCoreApplication>

class VisualRootItemTest : public QObject
{
    Q_OBJECT

public:
    VisualRootItemTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testType();

private:
    VisualRootItem *m_rootItem;
};

VisualRootItemTest::VisualRootItemTest()
    : m_rootItem(0)
{
}

void VisualRootItemTest::init()
{
    m_rootItem = new VisualRootItem();
}

void VisualRootItemTest::cleanup()
{
    delete m_rootItem;
}

void VisualRootItemTest::testType()
{
    QVERIFY2(m_rootItem->itemType() == VisualItem::VisualRootItem, "Visual root item returned wrong type");
}

QTEST_MAIN(VisualRootItemTest)

#include "tst_visualrootitemtest.moc"
