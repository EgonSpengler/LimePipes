/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALMEASURE_H
#define VISUALMEASURE_H

#include <QObject>
#include "abstractvisualitem.h"

class VisualMeasure : public AbstractVisualItem
{
public:
    explicit VisualMeasure(QObject *parent = 0);

    Type type() const;
    void setDataFromIndex(const QPersistentModelIndex &index);
};

#endif // VISUALMEASURE_H
