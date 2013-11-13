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
#include <itemdatatypes.h>
#include "../interactingiteminterface.h"
#include "../scorepropertiesitem.h"

class QGraphicsWidget;
class GraphicalScoreItem;
class ScorePropertiesDialog;

class InteractingScore : public QObject,
                         public InteractingItemInterface
{
    Q_OBJECT

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
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    ScorePropertiesItem *scorePropertiesItem() const;

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
    ScorePropertiesItem *m_scorePropertiesItem;
    GraphicalScoreItem *m_headerItem;
    GraphicalScoreItem *m_footerItem;
    ScorePropertiesDialog *m_scorePropertiesDialog;
};

#endif // INTERACTINGSCORE_H
