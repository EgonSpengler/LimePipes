/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "abstractscorepropertiesitemdummy.h"

AbstractScorePropertiesItemDummy::AbstractScorePropertiesItemDummy(QObject *parent)
    : AbstractScorePropertiesItem(parent)
{
}

void AbstractScorePropertiesItemDummy::setNewTitle(const QString &title)
{
    emit setNewTitleCalled();
}

void AbstractScorePropertiesItemDummy::setNewComposer(const QString &composer)
{
    emit setNewComposerCalled();
}

void AbstractScorePropertiesItemDummy::setNewArranger(const QString &arranger)
{
    emit setNewArrangerCalled();
}

void AbstractScorePropertiesItemDummy::setNewYear(const QString &year)
{
    emit setNewYearCalled();
}

void AbstractScorePropertiesItemDummy::setNewCopyright(const QString &copyright)
{
    emit setNewCopyrightCalled();
}

void AbstractScorePropertiesItemDummy::setNewTimeSignature(const TimeSignature &timeSig)
{
    emit setNewTimeSignatureCalled();
}
