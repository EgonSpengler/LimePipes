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
#include <datatypes/timesignature.h>

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
    setData(title, LP::ScoreTitle);
}

bool Score::itemSupportsWritingOfData(int role) const
{
    switch (role) {
    case LP::ScoreArranger:
    case LP::ScoreComposer:
    case LP::ScoreCopyright:
    case LP::ScoreTimeSignature:
    case LP::ScoreTitle:
    case LP::ScoreYear:
        return true;
    default:
        return false;
    }
}

void Score::writeItemDataToXmlStream(QXmlStreamWriter *writer)
{
    if (!textForScoreDataRole(LP::ScoreTitle).isEmpty())
        writer->writeTextElement("TITLE", textForScoreDataRole(LP::ScoreTitle));
    if (!textForScoreDataRole(LP::ScoreComposer).isEmpty())
        writer->writeTextElement("COMPOSER", textForScoreDataRole(LP::ScoreComposer));
    if (!textForScoreDataRole(LP::ScoreArranger).isEmpty())
        writer->writeTextElement("ARRANGER", textForScoreDataRole(LP::ScoreArranger));
    if (!textForScoreDataRole(LP::ScoreCopyright).isEmpty())
        writer->writeTextElement("COPYRIGHT", textForScoreDataRole(LP::ScoreCopyright));
    if (!textForScoreDataRole(LP::ScoreYear).isEmpty())
        writer->writeTextElement("YEAR", textForScoreDataRole(LP::ScoreYear));

    QVariant timeSigVar = data(LP::ScoreTimeSignature);
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
        setData(reader->readElementText(), LP::ScoreComposer);

    if (QString("ARRANGER").compare(reader->name(), Qt::CaseInsensitive) == 0)
        setData(reader->readElementText(), LP::ScoreArranger);

    if (QString("COPYRIGHT").compare(reader->name(), Qt::CaseInsensitive) == 0)
        setData(reader->readElementText(), LP::ScoreCopyright);

    if (QString("YEAR").compare(reader->name(), Qt::CaseInsensitive) == 0)
        setData(reader->readElementText(), LP::ScoreYear);

    if (TimeSignature::xmlTagName().compare(reader->name(), Qt::CaseInsensitive) == 0) {
        TimeSignature timeSig;
        timeSig.readFromXmlStream(reader);
        setData(QVariant::fromValue<TimeSignature>(timeSig), LP::ScoreTimeSignature);
    }
}

QString Score::textForScoreDataRole(LP::ScoreDataRole role)
{
    QVariant scoreData = data(role);
    if (scoreData.isValid())
        return scoreData.toString();
    return QString();
}
