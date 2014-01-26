/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <graphicsitemview/visualmusicmodel/visualitemfactory.h>
#include <graphicsitemview/visualmusicmodel/visualpart.h>
#include <graphicsitemview/visualmusicmodel/interactinggraphicsitems/interactinggraphicsitem.h>

class VisualItemFactoryTest : public QObject
{
    Q_OBJECT

public:
    VisualItemFactoryTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCreateScore();
    void testCreateTune();
    void testCreatePart();

private:
    VisualItemFactory *m_itemFactory;
};

VisualItemFactoryTest::VisualItemFactoryTest()
{
}

void VisualItemFactoryTest::initTestCase()
{
    m_itemFactory = new VisualItemFactory();
}

void VisualItemFactoryTest::cleanupTestCase()
{
    delete m_itemFactory;
}

void VisualItemFactoryTest::testCreateScore()
{
    VisualItem *score = m_itemFactory->createVisualItem(VisualItem::VisualScoreItem);
    QVERIFY2(score != 0, "Factory returned no score");
    QVERIFY2(score->itemType() == VisualItem::VisualScoreItem, "Factory returned wrong item type");
    QVERIFY2(score->graphicalType() == VisualItem::GraphicalRowType, "Factory wrong graphical type");
    QVERIFY2(score->rowCount() == 2, "Score item hasn't 2 row items");
    InteractingGraphicsItem *headerItem = score->rowGraphics().at(0);
    QVERIFY2(headerItem->itemInteraction() != 0, "Factory hasn't set an item interaction on header graphics item");
    InteractingGraphicsItem *footerItem = score->rowGraphics().at(1);
    QVERIFY2(footerItem->itemInteraction() != 0, "Factory hasn't set an item interaction on footer graphics item");
}

void VisualItemFactoryTest::testCreateTune()
{
    VisualItem *tune = m_itemFactory->createVisualItem(VisualItem::VisualTuneItem);
    QVERIFY2(tune != 0, "Factory returned no item");
    QVERIFY2(tune->itemType() == VisualItem::VisualTuneItem, "Factory returned wrong item type");
    QVERIFY2(tune->graphicalType() == VisualItem::GraphicalRowType, "Factory wrong graphical type");
    QVERIFY2(tune->rowCount() == 0, "Item hasn't correct row items count");
}

void VisualItemFactoryTest::testCreatePart()
{
    VisualItem *part = m_itemFactory->createVisualItem(VisualItem::VisualPartItem);
    QVERIFY2(part != 0, "Factory returned no item");
    QVERIFY2(part->itemType() == VisualItem::VisualPartItem, "Factory returned wrong item type");
    QVERIFY2(part->graphicalType() == VisualItem::GraphicalRowType, "Factory wrong graphical type");
}

QTEST_MAIN(VisualItemFactoryTest)

#include "tst_visualitemfactorytest.moc"
