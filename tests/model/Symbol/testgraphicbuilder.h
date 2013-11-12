/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TESTGRAPHICBUILDER_H
#define TESTGRAPHICBUILDER_H

#include <symbolgraphicbuilder.h>
#include <QObject>

class TestGraphicBuilder : public QObject,
                           public SymbolGraphicBuilder
{
    Q_OBJECT
public:
    explicit TestGraphicBuilder(MusicItem *item, QObject *parent = 0);
    ~TestGraphicBuilder() {}

    void createPixmaps(int lineHeight);
    void updateSymbolGraphic() { emit updateSymbolGraphicCalled(); }

    bool isSymbolGraphicAffectedByDataRole(int role) { Q_UNUSED(role) return true; }

signals:
    void createPixmapsCalled();
    void updateSymbolGraphicCalled();
};

#endif // TESTGRAPHICBUILDER_H
