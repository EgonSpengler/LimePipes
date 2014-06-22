/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "musiclayout.h"

MusicLayout::MusicLayout(QObject *parent)
    : QObject(parent),
      m_spaceAboveStaff(0)
{
}

double MusicLayout::spaceAboveStaff() const
{
    return m_spaceAboveStaff;
}

void MusicLayout::setSpaceAboveStaff(double staffSpacing)
{
    if (m_spaceAboveStaff == staffSpacing)
        return;

    m_spaceAboveStaff = staffSpacing;
    emit layoutChanged();
}
