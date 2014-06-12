/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TIEENGRAVER_H
#define TIEENGRAVER_H

#include <QList>
#include <QHash>

#include "baseengraver.h"

class SymbolGraphicBuilder;
class TieGraphicsItem;

class TieEngraver : public BaseEngraver
{
public:
    TieEngraver();

    // BaseEngraver interface
public:
    void insertGraphicsBuilder(int index, SymbolGraphicBuilder *builder);
    void removeGraphicsBuilder(SymbolGraphicBuilder *builder);

    SymbolSpanType spanTypeOfBuilder(SymbolGraphicBuilder *builder);
private:
    SymbolGraphicBuilder *startItemBuilderBefore(int index);
    SymbolGraphicBuilder *endItemBuilderAfter(int index);
    QList<SymbolGraphicBuilder*> m_graphicBuilder;
    QHash<SymbolGraphicBuilder*, TieGraphicsItem*> m_tieItems; // Contains pointers to TieGraphicsItems
                                                               // for every tie graphic builder
};

#endif // TIEENGRAVER_H
