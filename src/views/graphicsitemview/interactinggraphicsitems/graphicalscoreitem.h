/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GRAPHICALSCOREITEM_H
#define GRAPHICALSCOREITEM_H

#include <QGraphicsTextItem>
#include "interactinggraphicsitem.h"
#include "../graphicalscoreinterface.h"
#include "../scorepropertiesitem.h"

class GraphicalScoreItem : public ScorePropertiesItem,
                           public GraphicalScoreInterface,
                           public InteractingGraphicsItem
{
    friend class GraphicalScoreItemTest;

public:
    explicit GraphicalScoreItem(QObject *parent = 0);

    void setTitle(const QString& title);
    QString title() const;

private:
    QGraphicsTextItem *m_titleItem;

    // AbstractScorePropertiesHolder interface
public slots:
    void setNewTitle(const QString &title);
    void setNewComposer(const QString &composer);
    void setNewArranger(const QString &arranger);
    void setNewYear(const QString &year);
    void setNewCopyright(const QString &copyright);
    void setNewTimeSignature(const TimeSignature &timeSig);
};

#endif // GRAPHICALSCOREITEM_H
