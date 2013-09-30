/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALTUNE_H
#define VISUALTUNE_H

#include <QObject>
#include "abstractvisualitem.h"

class VisualTune : public QObject,
                       public AbstractVisualItem
{
public:
    explicit VisualTune(QObject *parent = 0);

    Type type() const;
    void setDataFromIndex(const QPersistentModelIndex &index);
};

#endif // VISUALTUNE_H
