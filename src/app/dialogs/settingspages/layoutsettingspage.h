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
#include <QVector>
#include <QPageSize>
#include <QPageLayout>

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

    void writeSettings();
private slots:
    void currentLayoutUnitChanged(int index);
    void currentPageSizeChanged(int index);
    void marginsChanged();
    void restoreDefaultPageSize();

private:
    void initPageFormatComboBox();
    void initLayoutUnitComboBox();
    void setUiFromPageLayout();
    void createConnections();
    QString pageLayoutUnitToString(const QPageLayout::Unit &unit);
    void setMarginSpinboxSuffixes(QString unitName);
    static QVector<QPageSize::PageSizeId> s_pageSizes;
    LayoutSettings *m_layoutSettings;
    QPageLayout m_pageLayout;
    Ui::LayoutSettingsPage *ui;
};

#endif // LAYOUTSETTINGSPAGE_H
