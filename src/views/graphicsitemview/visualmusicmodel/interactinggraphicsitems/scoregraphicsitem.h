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
#include <common/itemdataroles.h>
#include <common/settingdefines.h>
#include <common/settingsobserver.h>
#include "interactinggraphicsitem.h"
#include "graphicitems/textrowwidget.h"

class QGraphicsLinearLayout;

class ScoreGraphicsItem : public InteractingGraphicsItem,
                          public SettingsObserver
{
    Q_OBJECT

    friend class ScoreGraphicsItemTest;

public:
    explicit ScoreGraphicsItem(QGraphicsItem *parent = 0);
    explicit ScoreGraphicsItem(Settings::Score::Area area, QGraphicsItem *parent = 0);
    ~ScoreGraphicsItem();

    void setScoreArea(Settings::Score::Area area);
    Settings::Score::Area scoreArea() const;

    void setData(const QVariant &value, int key);

    void initialize();

    // SettingsObserver
    void notify();

signals:
    void itemTextChanged(const QVariant& text, int dataRole);

private slots:
    void itemInteractionChanged();
    void textRowItemChanged(Settings::TextAlignment position, const QString& newText);

private:
    class TextItemPosition {
    public:
        int rowIndex;
        Settings::TextAlignment rowPosition;
        bool operator ==(const TextItemPosition& other) const;
    };

    void setItemPosition(LP::ScoreDataRole itemType, int rowIndex, Settings::TextAlignment position);
    void removeItemPosition(LP::ScoreDataRole itemType);
    bool itemPositionIsInUse(int rowIndex, Settings::TextAlignment position);

    int rowIndexOfDataRole(LP::ScoreDataRole dataRole);
    Settings::TextAlignment rowAlignmentOfDataRole(LP::ScoreDataRole dataRole);
    bool hasItemPositionForDataRole(LP::ScoreDataRole itemType) const;

    void setItemText(LP::ScoreDataRole itemType, const QString& text);
    QString itemText(LP::ScoreDataRole itemType) const;

    void setItemFont(LP::ScoreDataRole itemType, const QFont& font);
    QFont itemFont(LP::ScoreDataRole itemType) const;

    void setItemColor(LP::ScoreDataRole itemType, const QColor& color);
    QColor itemColor(LP::ScoreDataRole itemType) const;

    int rowCount() const;

    void createConnections();
    void appendRow();
    void removeLastRow();
    void addRowsUntilRowIndex(int index);
    void deleteLastEmptyRows();
    void initFromSettings();
    void initItemDataFromSettings(LP::ScoreDataRole dataRole);
    void updateDataFromSettings();
    void updateItemDataFromSettings(LP::ScoreDataRole dataRole);
    QList<TextRowWidget*> m_textRows;
    QGraphicsLinearLayout *m_rowLayout;
    QHash<LP::ScoreDataRole, TextItemPosition> m_itemPositions;
    Settings::Score::Area m_scoreArea;
};

#endif // SCOREGRAPHICSITEM_H
