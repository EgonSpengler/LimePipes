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
#include <src/views/common/symbolgraphicbuilder.h>

namespace {

class TestMusicItem
{
public:
    TestMusicItem()
    { }

    static int initialDataRole;
};

}

int TestMusicItem::initialDataRole = 1234;

class TestGraphicBuilder : public SymbolGraphicBuilder
{
public:
    TestGraphicBuilder()
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
    TestGraphicBuilder *m_builder;
};

#endif
