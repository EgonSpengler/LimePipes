/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>

#include <symbolgraphicbuilder.h>
#include <musicitem.h>

namespace {

class TestMusicItem : public MusicItem
{
public:
    TestMusicItem()
        : MusicItem()
    {
        initData(1111, initialDataRole);
    }

    static int initialDataRole;

    bool itemSupportsWritingOfData(int role) const
    { Q_UNUSED(role) return true; }
};

int TestMusicItem::initialDataRole = 1234;

class TestGraphicBuilder : public SymbolGraphicBuilder
{
public:
    TestGraphicBuilder(MusicItem *item)
        : SymbolGraphicBuilder(item)
    {}

    void createPixmaps(qreal lineHeight) { Q_UNUSED(lineHeight) }
    void updateSymbolGraphic() { }

    QVariant getItemData(int role) {
        return SymbolGraphicBuilder::itemData(role);
    }

    void setGraphicPixmap(const QPixmap &pixmap) {
        setSymbolGraphicPixmap(pixmap);
    }

    void setGraphicYOffset(qreal yOffset) {
        setSymbolGraphicYOffset(yOffset);
    }

    bool isSymbolGraphicAffectedByDataRole(int role) { Q_UNUSED(role) return true; }
};

}

class SymbolGraphicBuilderTest : public QObject
{
    Q_OBJECT
    
public:
    SymbolGraphicBuilderTest() {}
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testSymbolGraphic();
    void testItemData();
    void testSetPixmap();
    void testSetYOffset();

private:
    MusicItem *m_musicItem;
    TestGraphicBuilder *m_builder;
};

void SymbolGraphicBuilderTest::init()
{
    m_musicItem = new TestMusicItem();
    m_builder = new TestGraphicBuilder(m_musicItem);
}

void SymbolGraphicBuilderTest::cleanup()
{
    delete m_builder;
    delete m_musicItem;
}

void SymbolGraphicBuilderTest::testSymbolGraphic()
{
    SymbolGraphicPtr symbolGraphic = m_builder->symbolGraphic();
    QVERIFY2(symbolGraphic->pixmap().isNull() == true, "SymbolGraphics pixmap was initially set");
}

void SymbolGraphicBuilderTest::testItemData()
{
    QVariant initialData = m_builder->getItemData(TestMusicItem::initialDataRole);
    QVERIFY2(initialData.isValid(), "Failed getting item data in subclass");
}

void SymbolGraphicBuilderTest::testSetPixmap()
{
    m_builder->setGraphicPixmap(QPixmap(30, 10));
    SymbolGraphicPtr symbolGraphic = m_builder->symbolGraphic();
    QVERIFY2(symbolGraphic->pixmap().width() == 30, "Failed setting pixmap");
}

void SymbolGraphicBuilderTest::testSetYOffset()
{
    m_builder->setGraphicYOffset(23.56);
    SymbolGraphicPtr symbolGraphic = m_builder->symbolGraphic();
    QVERIFY2(symbolGraphic->yOffset() == 23.56, "Failed setting y offset");
}

QTEST_MAIN(SymbolGraphicBuilderTest)

#include "tst_symbolgraphicbuildertest.moc"
