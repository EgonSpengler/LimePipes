/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QSettings>
#include <QPrinter>

#include "layoutsettings.h"

static const QString LayoutKey("layout");

static const QString PageSizeKey("pagesize");
static const QString OrientationKey("orientation");
static const QString UnitKey("unit");
static const QString LeftMarginKey("leftmargin");
static const QString TopMarginKey("topmargin");
static const QString BottomMarginKey("bottommargin");
static const QString RightMarginKey("rightmargin");

LayoutSettings::LayoutSettings(QObject *parent)
    : ObservableSettings(parent)
{
    m_settings = new QSettings(this);

    m_defaultPageLayout = QPrinter().pageLayout();
}

QPageLayout LayoutSettings::pageLayout()
{
    QPageLayout layout(m_defaultPageLayout);
    layout.setPageSize(QPageSize(pageSizeFromSettings()));
    layout.setUnits(unitFromSettings());
    layout.setOrientation(orientationFromSettings());
    layout.setMargins(marginsFromSettings());
    return layout;
}

QPageLayout LayoutSettings::defaultPageLayout()
{
    return m_defaultPageLayout;
}

void LayoutSettings::setPageLayout(const QPageLayout &pageLayout)
{
    setPageSize(pageLayout.pageSize().id());
    setUnit(pageLayout.units());
    setOrientation(pageLayout.orientation());
    setMargins(pageLayout.margins());

    notify(Settings::Category::Layout);
}

QString LayoutSettings::key(const QString &valueName) const
{
    return LayoutKey + QStringLiteral("/") + valueName;
}

QPageSize::PageSizeId LayoutSettings::pageSizeFromSettings() const
{
    int defaultSize = static_cast<int>(m_defaultPageLayout.pageSize().id());
    int value = m_settings->value(key(PageSizeKey), defaultSize).toInt();

    return static_cast<QPageSize::PageSizeId>(value);
}

void LayoutSettings::setPageSize(const QPageSize::PageSizeId &size)
{
    m_settings->setValue(key(PageSizeKey), static_cast<int>(size));
}

QPageLayout::Orientation LayoutSettings::orientationFromSettings() const
{
    int defaultOrientation = static_cast<int>(m_defaultPageLayout.orientation());
    int value = m_settings->value(key(OrientationKey), defaultOrientation).toInt();

    return static_cast<QPageLayout::Orientation>(value);
}

void LayoutSettings::setOrientation(QPageLayout::Orientation orientation)
{
    m_settings->setValue(key(OrientationKey), static_cast<int>(orientation));
}

QMarginsF LayoutSettings::marginsFromSettings() const
{
    QMarginsF defaultMargins = m_defaultPageLayout.margins();
    QMarginsF margins;
    margins.setTop(m_settings->value(key(TopMarginKey), defaultMargins.top()).toDouble());
    margins.setRight(m_settings->value(key(RightMarginKey), defaultMargins.top()).toDouble());
    margins.setBottom(m_settings->value(key(BottomMarginKey), defaultMargins.top()).toDouble());
    margins.setLeft(m_settings->value(key(LeftMarginKey), defaultMargins.top()).toDouble());

    return margins;
}

void LayoutSettings::setMargins(const QMarginsF &margins)
{
    m_settings->setValue(key(TopMarginKey), margins.top());
    m_settings->setValue(key(RightMarginKey), margins.right());
    m_settings->setValue(key(BottomMarginKey), margins.bottom());
    m_settings->setValue(key(LeftMarginKey), margins.left());
}

QPageLayout::Unit LayoutSettings::unitFromSettings() const
{
    int defaultUnit = static_cast<int>(m_defaultPageLayout.units());
    int unit = m_settings->value(key(UnitKey), defaultUnit).toInt();

    return static_cast<QPageLayout::Unit>(unit);
}

void LayoutSettings::setUnit(QPageLayout::Unit unit)
{
    m_settings->setValue(key(UnitKey), static_cast<int>(unit));
}
