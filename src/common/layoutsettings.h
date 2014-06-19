/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef LAYOUTSETTINGS_H
#define LAYOUTSETTINGS_H

#include <QPageLayout>
#include <QPageSize>
#include <QMarginsF>

#include "observablesettings.h"

class QSettings;

class LayoutSettings : public ObservableSettings
{
    Q_OBJECT
public:
    explicit LayoutSettings(QObject *parent = 0);

    QPageLayout pageLayout();
    QPageLayout defaultPageLayout();
    void setPageLayout(const QPageLayout &pageLayout);

private:
    QString key(const QString &valueName) const;

    QPageSize::PageSizeId pageSizeFromSettings() const;
    void setPageSize(const QPageSize::PageSizeId &size);

    QPageLayout::Orientation orientationFromSettings() const;
    void setOrientation(QPageLayout::Orientation orientation);

    QMarginsF marginsFromSettings() const;
    void setMargins(const QMarginsF &margins);

    QPageLayout::Unit unitFromSettings() const;
    void setUnit(QPageLayout::Unit unit);

    QPageLayout m_defaultPageLayout;
    QSettings *m_settings;
};

#endif // LAYOUTSETTINGS_H
