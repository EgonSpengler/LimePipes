/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALPART_H
#define VISUALPART_H

#include <QObject>
#include "abstractvisualitem.h"

class VisualPart : public QObject,
                   public AbstractVisualItem
{
public:
    explicit VisualPart(QObject *parent = 0);

    Type type() const;
    void setDataFromIndex(const QPersistentModelIndex &index);
};

#endif // VISUALPART_H
