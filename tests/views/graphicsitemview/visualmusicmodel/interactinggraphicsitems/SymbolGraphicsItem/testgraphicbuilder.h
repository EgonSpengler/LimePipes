/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TESTGRAPHICBUILDER_H
#define TESTGRAPHICBUILDER_H

#include <src/common/graphictypes/symbolgraphicbuilder.h>

class TestGraphicBuilder : public SymbolGraphicBuilder
{
public:
    explicit TestGraphicBuilder();

    // SymbolGraphicBuilder interface
public slots:
    void createPixmaps(int lineHeight);
    void updateSymbolGraphic();
    bool isSymbolGraphicAffectedByDataRole(int role);
};

#endif // TESTGRAPHICBUILDER_H
