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
#include "../interactingiteminterface.h"
#include "../scorepropertiesitem.h"

class QGraphicsWidget;
class GraphicalScoreItem;

class InteractingScore :  public ScorePropertiesItem,
                          public InteractingItemInterface
{
    friend class InteractingScoreTest;

public:
    explicit InteractingScore(QObject *parent = 0);
    ~InteractingScore();

    QGraphicsWidget *headerItem() const;
    QGraphicsWidget *footerItem() const;

    // InteractingItemInterface interface
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    // ScorePropertiesInterface interface
    void setTitle(const QString &title);
    void setComposer(const QString &composer);
    void setArranger(const QString &arranger);
    void setYear(const QString &year);
    void setCopyright(const QString &copyright);
    void setTimeSignature(const TimeSignature &timeSig);

private:
    GraphicalScoreItem *m_headerItem;
    GraphicalScoreItem *m_footerItem;
};

#endif // INTERACTINGSCORE_H
