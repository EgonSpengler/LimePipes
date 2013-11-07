/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GRAPHICALSCOREITEM_H
#define GRAPHICALSCOREITEM_H

#include <QList>
#include <QHash>
#include <itemdatatypes.h>
#include "interactinggraphicsitem.h"
#include "graphicitems/textrowwidget.h"
#include <graphicsitemview/scorepropertiesinterface.h>

class TextWidget;
class QGraphicsLinearLayout;

class GraphicalScoreItem : public InteractingGraphicsItem
{
    Q_OBJECT

    friend class GraphicalScoreItemTest;

public:
    explicit GraphicalScoreItem(QGraphicsItem *parent = 0);

    void setTitle(const QString& title);
    QString title() const;

    void setItemPosition(LP::ScoreDataRole itemType, int row, TextRowWidget::TextPosition position);
    void setItemFont(LP::ScoreDataRole itemType, const QFont& font);
    void setItemColor(LP::ScoreDataRole itemType, const QColor& color);

signals:
    void titleChanged(const QString& title);
    void composerChanged(const QString& composer);
    void arrangerChanged(const QString& arranger);
    void yearChanged(const QString& newYear);
    void copyrightChanged(const QString& newCopyright);
    void timeSignatureChanged(const TimeSignature& newTimeSignature);

private slots:
    void textRowItemChanged(TextRowWidget::TextPosition position, const QString& newText);

private:
    class ItemPosition {
    public:
        int rowIndex;
        TextRowWidget::TextPosition rowPosition;
        bool operator ==(const ItemPosition& other) const
        {
            if (rowIndex == other.rowIndex &&
                    rowPosition == other.rowPosition)
                return true;
            return false;
        }
    };

    void appendRow();
    void addRowsUntilRowIndex(int index);
    QList<TextRowWidget*> m_textRows;
    QGraphicsLinearLayout *m_rowLayout;
    QHash<LP::ScoreDataRole, ItemPosition> m_itemPostions;
};

#endif // GRAPHICALSCOREITEM_H
