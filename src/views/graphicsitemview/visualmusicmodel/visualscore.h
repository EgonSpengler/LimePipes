/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALSCORE_H
#define VISUALSCORE_H

#include <itemdatatypes.h>
#include "visualitem.h"

class ScoreGraphicsItem;

class VisualScore : public VisualItem
{
    Q_OBJECT
public:
    explicit VisualScore(QObject *parent = 0);

    // AbstractVisualItem interface
    ItemType itemType() const;
    void setDataFromIndex(const QPersistentModelIndex &index);

    GraphicalType graphicalType() const;
    QList<InteractingGraphicsItem *> rowGraphics() const;

    ScoreGraphicsItem *headerItem() const;
    ScoreGraphicsItem *footerItem() const;

private slots:
    void scoreGraphicsTextChanged(LP::ScoreDataRole data, const QString &text);

private:
    void createConnections();
    ScoreGraphicsItem *m_headerItem;
    ScoreGraphicsItem *m_footerItem;
};

#endif // VISUALSCORE_H
