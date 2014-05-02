/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QDebug>
#include <QVariant>
#include <QGraphicsLinearLayout>
#include <common/scoresettings.h>
#include "graphicitems/textwidget.h"
#include "graphicitems/textrowwidget.h"
#include <common/graphictypes/iteminteraction.h>
#include "scoregraphicsitem.h"

ScoreGraphicsItem::ScoreGraphicsItem(QGraphicsItem *parent)
    : InteractingGraphicsItem(parent),
      m_rowLayout(0),
      m_scoreArea(Settings::Score::NoArea)
{
    initialize();
}

ScoreGraphicsItem::ScoreGraphicsItem(Settings::Score::Area area, QGraphicsItem *parent)
    : InteractingGraphicsItem(parent),
      m_rowLayout(0),
      m_scoreArea(area)
{
    initialize();

    initFromSettings();
}

void ScoreGraphicsItem::initialize()
{
    m_rowLayout = new QGraphicsLinearLayout(Qt::Vertical, this);
    m_rowLayout->setContentsMargins(0, 0, 0, 0);

    setSettingsCategory(Settings::Category::Score);
    ScoreSettings::registerObserver(this);

    createConnections();
}

ScoreGraphicsItem::~ScoreGraphicsItem()
{
    ScoreSettings::unregisterObserver(this);
}

void ScoreGraphicsItem::setScoreArea(Settings::Score::Area area)
{
    if (m_scoreArea == area)
        return;

    m_scoreArea = area;
    initFromSettings();
}

Settings::Score::Area ScoreGraphicsItem::scoreArea() const
{
    return m_scoreArea;
}

void ScoreGraphicsItem::appendRow()
{
    TextRowWidget *newRow = new TextRowWidget();
    m_textRows.append(newRow);
    m_rowLayout->addItem(newRow);

    connect(newRow, &TextRowWidget::textChanged,
            this, &ScoreGraphicsItem::textRowItemChanged);
}

void ScoreGraphicsItem::removeLastRow()
{
    if (m_textRows.isEmpty())
        return;

    TextRowWidget *rowWidget = m_textRows.takeLast();
    m_rowLayout->removeItem(rowWidget);
    delete rowWidget;
}

void ScoreGraphicsItem::createConnections()
{
    connect(this, &InteractingGraphicsItem::itemInteractionChanged,
            this, &ScoreGraphicsItem::itemInteractionChanged);
}

void ScoreGraphicsItem::itemInteractionChanged()
{
    // Connect to new item interaction object
    ItemInteraction *interaction = itemInteraction();
    if (interaction == 0) return;

    connect(this, &ScoreGraphicsItem::itemTextChanged,
            interaction, &ItemInteraction::dataChanged);
}

void ScoreGraphicsItem::textRowItemChanged(Settings::TextAlignment position, const QString &newText)
{
    QObject *senderRow = sender();
    TextRowWidget *rowWidget = qobject_cast<TextRowWidget*>(senderRow);
    if (!rowWidget) return;

    int rowIndex = m_textRows.indexOf(rowWidget);
    if (rowIndex == -1) return;

    TextItemPosition itemPosition;
    itemPosition.rowIndex = rowIndex;
    itemPosition.rowPosition = position;

    if (!m_itemPositions.values().contains(itemPosition))
        return;

    LP::ScoreDataRole itemType = m_itemPositions.key(itemPosition);
    emit itemTextChanged(newText, itemType);
}

void ScoreGraphicsItem::addRowsUntilRowIndex(int index)
{
    if (m_rowLayout->count() >= index + 1)
        return;

    while (m_rowLayout->count() < index + 1) {
        appendRow();
    }
}

void ScoreGraphicsItem::deleteLastEmptyRows()
{
    int lastRowWithContent = 0;
    auto iterator = m_itemPositions.constBegin();
    while (iterator != m_itemPositions.constEnd()) {
        if (iterator.value().rowIndex > lastRowWithContent) {
            lastRowWithContent = iterator.value().rowIndex;
        }
        ++iterator;
    }

    if (!m_rowLayout->count() > lastRowWithContent + 1)
        return;

    while (m_rowLayout->count() > lastRowWithContent + 1) {
        removeLastRow();
    }
}

void ScoreGraphicsItem::initFromSettings()
{
    initItemDataFromSettings(LP::ScoreTitle);
    initItemDataFromSettings(LP::ScoreComposer);
    initItemDataFromSettings(LP::ScoreArranger);
    initItemDataFromSettings(LP::ScoreType);
    initItemDataFromSettings(LP::ScoreYear);
    initItemDataFromSettings(LP::ScoreCopyright);
}

void ScoreGraphicsItem::initItemDataFromSettings(LP::ScoreDataRole dataRole)
{
    using namespace Settings;
    using namespace Settings::Score;

    if (m_scoreArea == NoArea)
        return;

    ScoreSettings settings(m_scoreArea, dataRole);
    bool itemEnabled =  settings.value(Enabled).toBool();
    if (itemEnabled) {
        TextItemPosition position;
        position.rowIndex = settings.value(Row).toInt();
        if (position.rowIndex > 0)
            position.rowIndex -= 1;
        position.rowPosition = settings.value(Alignment).value<TextAlignment>();

        if (itemPositionIsInUse(position.rowIndex, position.rowPosition)) {
            qWarning() << QString("Text item position (row: %1, alignment: %2) is already in use and can't be initialized with setting.")
                          .arg(position.rowIndex + 1)
                          .arg(static_cast<int>(position.rowPosition));
            return;
        }

        updateItemDataFromSettings(dataRole);
    }
}

void ScoreGraphicsItem::setItemPosition(LP::ScoreDataRole itemType, int rowIndex, Settings::TextAlignment position)
{
    if (rowIndex < 0)
        return;

    if (itemPositionIsInUse(rowIndex, position))
        return;

    TextItemPosition itemPosition;
    if (hasItemPositionForDataRole(itemType))
        itemPosition = m_itemPositions.value(itemType);

    addRowsUntilRowIndex(rowIndex);
    itemPosition.rowIndex = rowIndex;
    itemPosition.rowPosition = position;

    m_itemPositions.insert(itemType, itemPosition);

    deleteLastEmptyRows();
}

void ScoreGraphicsItem::removeItemPosition(LP::ScoreDataRole itemType)
{
    setItemText(itemType, "");
    m_itemPositions.remove(itemType);
    deleteLastEmptyRows();
}

bool ScoreGraphicsItem::itemPositionIsInUse(int rowIndex, Settings::TextAlignment position)
{
    TextItemPosition itemPosition;
    itemPosition.rowIndex = rowIndex;
    itemPosition.rowPosition = position;

    if (m_itemPositions.values().contains(itemPosition))
        return true;

    return false;
}

int ScoreGraphicsItem::rowIndexOfDataRole(LP::ScoreDataRole dataRole)
{
    if (!m_itemPositions.contains(dataRole))
        return -1;

    TextItemPosition itemPosition = m_itemPositions.value(dataRole);
    return itemPosition.rowIndex;
}

Settings::TextAlignment ScoreGraphicsItem::rowAlignmentOfDataRole(LP::ScoreDataRole dataRole)
{
    if (!m_itemPositions.contains(dataRole))
        return Settings::TextAlignment::NoAlignment;

    TextItemPosition itemPosition = m_itemPositions.value(dataRole);
    return itemPosition.rowPosition;
}

bool ScoreGraphicsItem::hasItemPositionForDataRole(LP::ScoreDataRole itemType) const
{
    if (m_itemPositions.contains(itemType))
        return true;
    return false;
}

void ScoreGraphicsItem::setItemText(LP::ScoreDataRole itemType, const QString &text)
{
    if (!hasItemPositionForDataRole(itemType)) {
        return;
    }

    TextItemPosition position = m_itemPositions.value(itemType);
    if (m_textRows.count() - 1 > position.rowIndex)
        addRowsUntilRowIndex(position.rowIndex);

    TextRowWidget *row = m_textRows.at(position.rowIndex);
    if (row->text(position.rowPosition) != text)
        row->setText(position.rowPosition, text);
}

QString ScoreGraphicsItem::itemText(LP::ScoreDataRole itemType) const
{
    if (!hasItemPositionForDataRole(itemType))
        return QString();

    TextItemPosition position = m_itemPositions.value(itemType);
    if (!m_textRows.count() > position.rowIndex)
        return QString();

    TextRowWidget *row = m_textRows.at(position.rowIndex);
    return row->text(position.rowPosition);
}

void ScoreGraphicsItem::setItemFont(LP::ScoreDataRole itemType, const QFont &font)
{
    if (!hasItemPositionForDataRole(itemType))
        return;

    TextItemPosition position = m_itemPositions.value(itemType);
    if (m_textRows.count() - 1 > position.rowIndex)
        addRowsUntilRowIndex(position.rowIndex);

    TextRowWidget *row = m_textRows.at(position.rowIndex);
    row->setFont(position.rowPosition, font);
}

QFont ScoreGraphicsItem::itemFont(LP::ScoreDataRole itemType) const
{
    if (!hasItemPositionForDataRole(itemType))
        return QFont();

    TextItemPosition position = m_itemPositions.value(itemType);
    if (!m_textRows.count() > position.rowIndex)
        return QFont();

    TextRowWidget *row = m_textRows.at(position.rowIndex);
    return row->font(position.rowPosition);
}

void ScoreGraphicsItem::setItemColor(LP::ScoreDataRole itemType, const QColor &color)
{
    if (!hasItemPositionForDataRole(itemType))
        return;

    TextItemPosition position = m_itemPositions.value(itemType);
    if (m_textRows.count() - 1 > position.rowIndex)
        addRowsUntilRowIndex(position.rowIndex);

    TextRowWidget *row = m_textRows.at(position.rowIndex);
    row->setColor(position.rowPosition, color);
}

QColor ScoreGraphicsItem::itemColor(LP::ScoreDataRole itemType) const
{
    if (!hasItemPositionForDataRole(itemType))
        return QColor();

    TextItemPosition position = m_itemPositions.value(itemType);
    if (!m_textRows.count() > position.rowIndex)
        return QColor();

    TextRowWidget *row = m_textRows.at(position.rowIndex);
    return row->color(position.rowPosition);
}

int ScoreGraphicsItem::rowCount() const
{
    return m_rowLayout->count();
}

void ScoreGraphicsItem::setData(const QVariant &value, int key)
{
    InteractingGraphicsItem::setData(value, key);
    setItemText(static_cast<LP::ScoreDataRole>(key), value.toString());
}

bool ScoreGraphicsItem::TextItemPosition::operator ==(const ScoreGraphicsItem::TextItemPosition &other) const
{
    if (rowIndex == other.rowIndex &&
            rowPosition == other.rowPosition)
        return true;
    return false;
}


void ScoreGraphicsItem::notify()
{
    updateDataFromSettings();
}

void ScoreGraphicsItem::updateDataFromSettings()
{
    updateItemDataFromSettings(LP::ScoreTitle);
    updateItemDataFromSettings(LP::ScoreComposer);
    updateItemDataFromSettings(LP::ScoreArranger);
    updateItemDataFromSettings(LP::ScoreType);
    updateItemDataFromSettings(LP::ScoreYear);
    updateItemDataFromSettings(LP::ScoreCopyright);
}

void ScoreGraphicsItem::updateItemDataFromSettings(LP::ScoreDataRole dataRole)
{
    using namespace Settings;
    using namespace Settings::Score;

    if (m_scoreArea == NoArea)
        return;

    ScoreSettings settings(m_scoreArea, dataRole);
    bool itemEnabled =  settings.value(Enabled).toBool();
    if (itemEnabled) {
        TextItemPosition position;
        position.rowIndex = settings.value(Row).toInt();
        if (position.rowIndex > 0)
            position.rowIndex -= 1;
        position.rowPosition = settings.value(Alignment).value<TextAlignment>();

        setItemPosition(dataRole, position.rowIndex, position.rowPosition);

        setItemFont(dataRole, settings.value(Font).value<QFont>());
        setItemColor(dataRole, settings.value(Color).value<QColor>());
    }
}
