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

#include <common/graphictypes/MusicFont/musicfont.h>

#include "observablesettings.h"

class QSettings;

//class MusicSheetLayout {

//public:
//    MusicSheetLayout()
//    {}
//};

class LayoutSettings : public ObservableSettings
{
    Q_OBJECT
public:
    explicit LayoutSettings(QObject *parent = 0);

    QPageLayout pageLayout() const;
    QPageLayout defaultPageLayout() const;
    void setPageLayout(const QPageLayout &pageLayout);

//    MusicSheetLayout musicSheetLayout() const;

    static QString pageLayoutUnitToString(const QPageLayout::Unit &unit);

    /*!
     * \brief staffSpace Staff space in millimeter
     * \return
     */
    double staffSpaceMM() const;
    void setStaffSpaceMM(const double &staffSpaceMM);

    int staffSpacePixel() const;

    static MusicFontPtr musicFont();
    static void setMusicFont(const MusicFontPtr &value);

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
    static MusicFontPtr s_musicFont;
};

#endif // LAYOUTSETTINGS_H
