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

#include "observablesettings.h"

class QSettings;

class LayoutSettings : public ObservableSettings
{
    Q_OBJECT
public:
    explicit LayoutSettings(QObject *parent = 0);

    QPageLayout pageLayout();

private:
    QPageLayout m_defaultPageLayout;
    QSettings *m_settings;
};

#endif // LAYOUTSETTINGS_H
