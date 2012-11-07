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

Score::Score(MusicItem *parent)
    : MusicItem(MusicItem::ScoreType, MusicItem::TuneType, parent)
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

void Score::readCurrentElementFromXmlStream(QXmlStreamReader *reader)
{
    if (QString("TITLE").compare(reader->name(), Qt::CaseInsensitive) == 0)
        setTitle(reader->readElementText());

    if (QString("COMPOSER").compare(reader->name(), Qt::CaseInsensitive) == 0)
        setData(reader->readElementText(), LP::scoreComposer);

    if (QString("ARRANGER").compare(reader->name(), Qt::CaseInsensitive) == 0)
        setData(reader->readElementText(), LP::scoreArranger);

    if (QString("COPYRIGHT").compare(reader->name(), Qt::CaseInsensitive) == 0)
        setData(reader->readElementText(), LP::scoreCopyright);

    if (QString("YEAR").compare(reader->name(), Qt::CaseInsensitive) == 0)
        setData(reader->readElementText(), LP::scoreYear);

    if (TimeSignature::xmlTagName().compare(reader->name(), Qt::CaseInsensitive) == 0) {
        TimeSignature timeSig;
        timeSig.readFromXmlStream(reader);
        setData(QVariant::fromValue<TimeSignature>(timeSig), LP::scoreTimeSignature);
    }
}

QString Score::textDataForRole(LP::DataRole role)
{
    QVariant scoreData = data(role);
    if (scoreData.isValid())
        return scoreData.toString();
    return QString();
}
