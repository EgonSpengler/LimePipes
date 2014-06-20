/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALITEMFACTORY_H
#define VISUALITEMFACTORY_H

#include "abstractvisualitemfactory.h"

class VisualItemFactory : public AbstractVisualItemFactory
{
public:
    explicit VisualItemFactory() {}

    VisualItem *createVisualItem(VisualItem::ItemType type);
    VisualItem *createVisualSymbol(int symbolType);

private:
    VisualItem *newVisualScore();
    VisualItem *newVisualTune();
    VisualItem *newVisualPart();
    VisualItem *newVisualMeasure();
    VisualItem *newVisualSymbol(int symbolType);
};

#endif // VISUALITEMFACTORY_H
