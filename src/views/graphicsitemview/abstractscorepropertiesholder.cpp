/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "abstractscorepropertiesholder.h"

AbstractScorePropertiesHolder::AbstractScorePropertiesHolder(QObject *parent)
    : QObject(parent)
{
}

void AbstractScorePropertiesHolder::setScoreProperties(ScorePropertiesInterface *scoreProperties)
{
    m_scoreProperties = scoreProperties;
}

ScorePropertiesInterface *AbstractScorePropertiesHolder::scoreProperties() const
{
    return m_scoreProperties;
}
