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
#include "abstractvisualitem.h"

class VisualSymbol : public QObject,
                     public AbstractVisualItem
{
public:
    explicit VisualSymbol(QObject *parent = 0);

    Type type() const;
    void setDataFromIndex(const QPersistentModelIndex &index);
};

#endif // VISUALSYMBOL_H
