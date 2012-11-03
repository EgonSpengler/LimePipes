/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class Score
  * A Score represents a container for one or more @ref Tune "Tunes" and has at least a title.
  */

#include "score.h"
#include <QXmlStreamWriter>
#include <timesignature.h>

Score::Score()
    : MusicItem(MusicItem::ScoreType, MusicItem::TuneType)
{
}

Score::Score(const QString &title)
    : MusicItem(MusicItem::ScoreType, MusicItem::TuneType)
{
    setTitle(title);
}

void Score::setTitle(const QString &title)
{
    setData(title, LP::scoreTitle);
}

bool Score::itemSupportsWritingOfData(int role) const
{
    switch (role) {
    case LP::scoreArranger:
    case LP::scoreComposer:
    case LP::scoreCopyright:
    case LP::scoreTimeSignature:
    case LP::scoreTitle:
    case LP::scoreYear:
        return true;
    default:
        return false;
    }
}

void Score::writeItemDataToXmlStream(QXmlStreamWriter *writer)
{
    if (!textDataForRole(LP::scoreTitle).isEmpty())
        writer->writeTextElement("TITLE", textDataForRole(LP::scoreTitle));
    if (!textDataForRole(LP::scoreComposer).isEmpty())
        writer->writeTextElement("COMPOSER", textDataForRole(LP::scoreComposer));
    if (!textDataForRole(LP::scoreArranger).isEmpty())
        writer->writeTextElement("ARRANGER", textDataForRole(LP::scoreArranger));
    if (!textDataForRole(LP::scoreCopyright).isEmpty())
        writer->writeTextElement("COPYRIGHT", textDataForRole(LP::scoreCopyright));
    if (!textDataForRole(LP::scoreYear).isEmpty())
        writer->writeTextElement("YEAR", textDataForRole(LP::scoreYear));

    QVariant timeSigVar = data(LP::scoreTimeSignature);
    if (timeSigVar.isValid() &&
        timeSigVar.canConvert<TimeSignature>()) {
        TimeSignature timeSig = timeSigVar.value<TimeSignature>();
        timeSig.writeToXmlStream(writer);
    }
}

QString Score::textDataForRole(LP::DataRole role)
{
    QVariant scoreData = data(role);
    if (scoreData.isValid())
        return scoreData.toString();
    return QString();
}
