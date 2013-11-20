/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <views/graphicsitemview/visualmusicmodel/visualitem.h>
#include <QtTest/QtTest>

class VisualItemTest : public QObject
{
    Q_OBJECT
    
public:
    VisualItemTest();
    
private Q_SLOTS:
    void init();
    void cleanup();

private:
    VisualItem *visualItem;
};

VisualItemTest::VisualItemTest()
    : visualItem(0)
{
}

void VisualItemTest::init()
{
    visualItem = new VisualItem();
}

void VisualItemTest::cleanup()
{
    delete visualItem;
}

QTEST_APPLESS_MAIN(VisualItemTest)

#include "tst_visualitemtest.moc"
