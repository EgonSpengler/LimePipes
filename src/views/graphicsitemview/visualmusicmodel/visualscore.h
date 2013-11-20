/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALSCORE_H
#define VISUALSCORE_H

#include "abstractvisualitem.h"

class VisualScore : public VisualItem
{
    Q_OBJECT
public:
    explicit VisualScore(QObject *parent = 0);

    // AbstractVisualItem interface
    ItemType itemType() const;
    void setDataFromIndex(const QPersistentModelIndex &index);

private slots:
    void titleChanged(const QString &title);

private:
    void createConnections();
};

#endif // VISUALSCORE_H
