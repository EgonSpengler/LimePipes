/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALSCORE_H
#define VISUALSCORE_H

#include "../scorepropertiesitem.h"
#include "abstractvisualitem.h"

class VisualScore : public AbstractVisualItem,
                    public ScorePropertiesItem
{
public:
    explicit VisualScore(QObject *parent = 0);

    // AbstractVisualItem interface
    Type type() const;
    void setDataFromIndex(const QPersistentModelIndex &index);
};

#endif // VISUALSCORE_H
