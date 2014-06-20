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
      m_staffSpacing(0)
{
}

double MusicLayout::staffSpacing() const
{
    return m_staffSpacing;
}

void MusicLayout::setStaffSpacing(double staffSpacing)
{
    if (m_staffSpacing == staffSpacing)
        return;

    m_staffSpacing = staffSpacing;
    emit layoutChanged();
}
