/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef LAYOUTSETTINGSPAGE_H
#define LAYOUTSETTINGSPAGE_H

#include <QFrame>

namespace Ui {
class LayoutSettingsPage;
}

class LayoutSettings;

class LayoutSettingsPage : public QFrame
{
    Q_OBJECT

public:
    explicit LayoutSettingsPage(QWidget *parent = 0);
    ~LayoutSettingsPage();

private:
    LayoutSettings *m_layoutSettings;
    Ui::LayoutSettingsPage *ui;
};

#endif // LAYOUTSETTINGSPAGE_H
