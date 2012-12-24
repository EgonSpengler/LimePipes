/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLGRAPHICBUILDERTEST_H
#define SYMBOLGRAPHICBUILDERTEST_H

#include <QObject>
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
    void writeItemDataToXmlStream(QXmlStreamWriter *writer) { Q_UNUSED(writer) }
    void readCurrentElementFromXmlStream(QXmlStreamReader *reader) { Q_UNUSED(reader) }
};

}

int TestMusicItem::initialDataRole = 1234;

class TestGraphicBuilder : public SymbolGraphicBuilder
{
public:
    TestGraphicBuilder(MusicItem *item)
        : SymbolGraphicBuilder(item)
    {}

    void createPixmaps(int lineHeight) { Q_UNUSED(lineHeight) }
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

#endif
