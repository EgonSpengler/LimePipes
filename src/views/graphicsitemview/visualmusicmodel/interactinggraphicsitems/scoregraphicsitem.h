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

    friend class ScoreGraphicsItemTest;

public:
    explicit ScoreGraphicsItem(QGraphicsItem *parent = 0);

    void setItemPosition(LP::ScoreDataRole itemType, int row, TextRowWidget::RowAlignment position);
    void removeItemPosition(LP::ScoreDataRole itemType);

    int rowOfDataRole(LP::ScoreDataRole dataRole);
    TextRowWidget::RowAlignment rowAlignmentOfDataRole(LP::ScoreDataRole dataRole);
    bool hasItemPositionForDataRole(LP::ScoreDataRole itemType) const;

    void setItemText(LP::ScoreDataRole itemType, const QString& text);
    QString itemText(LP::ScoreDataRole itemType) const;

    void setItemFont(LP::ScoreDataRole itemType, const QFont& font);
    QFont itemFont(LP::ScoreDataRole itemType) const;

    void setItemColor(LP::ScoreDataRole itemType, const QColor& color);
    QColor itemColor(LP::ScoreDataRole itemType) const;

    int rowCount() const;

    void setData(const QVariant &value, int key);

signals:
    void itemTextChanged(const QVariant& text, int dataRole);

private slots:
    void itemInteractionChanged();
    void textRowItemChanged(TextRowWidget::RowAlignment position, const QString& newText);

private:
    class TextItemPosition {
    public:
        int rowIndex;
        TextRowWidget::RowAlignment rowPosition;
        bool operator ==(const TextItemPosition& other) const;
    };

    void createConnections();
    void appendRow();
    void removeLastRow();
    void addRowsUntilRowIndex(int index);
    void deleteLastEmptyRows();
    QList<TextRowWidget*> m_textRows;
    QGraphicsLinearLayout *m_rowLayout;
    QHash<LP::ScoreDataRole, TextItemPosition> m_itemPositions;
};

#endif // SCOREGRAPHICSITEM_H
