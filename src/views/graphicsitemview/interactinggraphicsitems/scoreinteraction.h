/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCOREINTERACTION_H
#define SCOREINTERACTION_H

#include <QObject>
#include <itemdatatypes.h>
#include "../iteminteraction.h"

class QGraphicsWidget;
class ScoreGraphicsItem;
class ScorePropertiesDialog;

class ScoreInteraction : public ItemInteraction
{
    friend class ScoreInteractionTest;

public:
    explicit ScoreInteraction(QObject *parent = 0);
    ~ScoreInteraction();

    QGraphicsWidget *headerItem() const;
    QGraphicsWidget *footerItem() const;

    // InteractingItemInterface interface
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private slots:
    void propertyTextChanged(LP::ScoreDataRole dataRole, const QString& text);
    void propertyFontChanged(LP::ScoreDataRole dataRole, const QFont& font);
    void propertyColorChanged(LP::ScoreDataRole dataRole, const QColor &color);

    // Slots for ScorePropertiesItem signals
    void setTitle(const QString &title);
    void setType(const QString& type);
    void setComposer(const QString &composer);
    void setArranger(const QString &arranger);
    void setYear(const QString &year);
    void setCopyright(const QString &copyright);

private:
    void createConnections();
    ScoreGraphicsItem *m_headerItem;
    ScoreGraphicsItem *m_footerItem;
    ScorePropertiesDialog *m_scorePropertiesDialog;
};

#endif // SCOREINTERACTION_H
