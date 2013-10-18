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

class ScorePropertiesItem;

class VisualScore : public AbstractVisualItem
{
    Q_OBJECT
public:
    explicit VisualScore(QObject *parent = 0);

    // AbstractVisualItem interface
    Type type() const;
    void setDataFromIndex(const QPersistentModelIndex &index);

    ScorePropertiesItem *scorePropertiesItem() const;

private slots:
    void titleChanged(const QString &title);

private:
    void createConnections();
    ScorePropertiesItem *m_scorePropertiesItem;
};

#endif // VISUALSCORE_H
