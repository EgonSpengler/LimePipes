/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALSYMBOL_H
#define VISUALSYMBOL_H

#include <QObject>
#include "visualitem.h"

class VisualSymbol : public VisualItem
{
public:
    explicit VisualSymbol(QObject *parent = 0);

    ItemType itemType() const;
    void setDataFromIndex(const QPersistentModelIndex &index);
};

#endif // VISUALSYMBOL_H
