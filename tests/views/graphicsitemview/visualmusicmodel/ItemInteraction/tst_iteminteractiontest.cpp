/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <QGraphicsScene>
#include <views/graphicsitemview/visualmusicmodel/iteminteraction.h>

class ItemInteractionTest : public QObject
{
    Q_OBJECT
    
public:
    ItemInteractionTest();
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testSetGetGraphicsScene();

private:
    ItemInteraction *m_itemInteraction;
};

ItemInteractionTest::ItemInteractionTest()
    : m_itemInteraction(0)
{
}

void ItemInteractionTest::init()
{
    m_itemInteraction = new ItemInteraction();
}

void ItemInteractionTest::cleanup()
{
    delete m_itemInteraction;
}

void ItemInteractionTest::testSetGetGraphicsScene()
{
    QGraphicsScene *scene = new QGraphicsScene(this);

    m_itemInteraction->setGraphicsScene(scene);

    QVERIFY2(m_itemInteraction->graphicsScene() == scene, "Can't set QGraphicsScene and get it back");
}

QTEST_MAIN(ItemInteractionTest)

#include "tst_iteminteractiontest.moc"
