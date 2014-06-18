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

LayoutSettings::LayoutSettings(QObject *parent)
    : ObservableSettings(parent)
{
    m_settings = new QSettings(this);

    m_defaultPageLayout = QPrinter().pageLayout();
}

QPageLayout LayoutSettings::pageLayout()
{
    return m_defaultPageLayout;
}
