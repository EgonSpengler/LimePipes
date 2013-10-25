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
    enum TextItemType {
        Title,
        Composer,
        Arranger
    };

    explicit GraphicalScoreItem(QGraphicsItem *parent = 0);

    void setTitle(const QString& title);
    QString title() const;

signals:
    void titleChanged(const QString& title);

private:
    struct ItemPosition {
        int rowIndex;
        TextRowWidget::TextPosition rowPosition;
    };

    void appendRow();
    void addRowsUntilRowIndex(int index);
    QList<TextRowWidget*> m_textRows;
    QGraphicsLinearLayout *m_rowLayout;
    QHash<TextItemType, ItemPosition> m_itemPostions;
};

#endif // GRAPHICALSCOREITEM_H
