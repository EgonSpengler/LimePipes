/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef INTERACTINGSCORE_H
#define INTERACTINGSCORE_H

#include <QObject>
#include "../graphicalscoreinterface.h"
#include "../interactingiteminterface.h"
#include "../abstractscorepropertiesitem.h"

class GraphicalScoreItem;

class InteractingScore :  public AbstractScorePropertiesItem,
                          public GraphicalScoreInterface,
                          public InteractingItemInterface
{
public:
    explicit InteractingScore(QObject *parent = 0);
    ~InteractingScore();

    GraphicalScoreItem *headerItem() const { return m_headerItem; }
    GraphicalScoreItem *footerItem() const { return m_footerItem; }

    // InteractingItemInterface interface
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    // AbstractScorePropertiesItem interface
public slots:
    void setNewTitle(const QString &title);
    void setNewComposer(const QString &composer);
    void setNewArranger(const QString &arranger);
    void setNewYear(const QString &year);
    void setNewCopyright(const QString &copyright);
    void setNewTimeSignature(const TimeSignature &timeSig);

private:
    GraphicalScoreItem *m_headerItem;
    GraphicalScoreItem *m_footerItem;
};

#endif // INTERACTINGSCORE_H
