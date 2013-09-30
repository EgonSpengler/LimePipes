/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "scorepropertiesitem.h"

ScorePropertiesItem::ScorePropertiesItem()
{
}


QString ScorePropertiesItem::title() const
{
    return m_title;
}

void ScorePropertiesItem::setTitle(const QString &title)
{
    m_title = title;
}

QString ScorePropertiesItem::composer() const
{
    return m_composer;
}

void ScorePropertiesItem::setComposer(const QString &composer)
{
    m_composer = composer;
}
