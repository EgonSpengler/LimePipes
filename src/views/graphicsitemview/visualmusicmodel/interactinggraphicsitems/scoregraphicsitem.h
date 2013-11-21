/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCOREGRAPHICSITEM_H
#define SCOREGRAPHICSITEM_H

#include <QList>
#include <QHash>
#include <itemdatatypes.h>
#include "interactinggraphicsitem.h"
#include "graphicitems/textrowwidget.h"

class QGraphicsLinearLayout;

class ScoreGraphicsItem : public InteractingGraphicsItem
{
    Q_OBJECT

    friend class GraphicalScoreItemTest;

public:
    explicit ScoreGraphicsItem(QGraphicsItem *parent = 0);

    void setItemPosition(LP::ScoreDataRole itemType, int row, TextRowWidget::RowAlignment position);
    bool hasItemPositionForDataRole(LP::ScoreDataRole itemType);

    void setItemText(LP::ScoreDataRole itemType, const QString& text);
    QString itemText(LP::ScoreDataRole itemType);

    void setItemFont(LP::ScoreDataRole itemType, const QFont& font);
    void setItemColor(LP::ScoreDataRole itemType, const QColor& color);

signals:
    void itemTextChanged(LP::ScoreDataRole dataRole, const QString& text);

private slots:
    void textRowItemChanged(TextRowWidget::RowAlignment position, const QString& newText);

private:
    class TextItemPosition {
    public:
        int rowIndex;
        TextRowWidget::RowAlignment rowPosition;
        bool operator ==(const TextItemPosition& other) const;
    };

    void appendRow();
    void addRowsUntilRowIndex(int index);
    QList<TextRowWidget*> m_textRows;
    QGraphicsLinearLayout *m_rowLayout;
    QHash<LP::ScoreDataRole, TextItemPosition> m_itemPositions;
};

#endif // SCOREGRAPHICSITEM_H
