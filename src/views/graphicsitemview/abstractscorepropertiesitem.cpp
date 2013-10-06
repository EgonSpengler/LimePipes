/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "abstractscorepropertiesitem.h"

AbstractScorePropertiesItem::AbstractScorePropertiesItem(QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<TimeSignature>("TimeSignature");
}

void AbstractScorePropertiesItem::linkWithItem(AbstractScorePropertiesItem *item)
{
    // Title
    connect(this, SIGNAL(titleChanged(QString)),
            item, SLOT(setNewTitle(QString)));
    connect(item, SIGNAL(titleChanged(QString)),
            this, SLOT(setNewTitle(QString)));
}


QString AbstractScorePropertiesItem::title() const
{
    return m_title;
}

void AbstractScorePropertiesItem::setTitle(const QString &title)
{
    if (m_title == title) return;

    m_title = title;
    emit titleChanged(title);
}

QString AbstractScorePropertiesItem::composer() const
{
    return m_composer;
}

void AbstractScorePropertiesItem::setComposer(const QString &composer)
{
    if (m_composer == composer) return;

    m_composer = composer;
    emit composerChanged(composer);
}


QString AbstractScorePropertiesItem::arranger() const
{
    return m_arranger;
}

void AbstractScorePropertiesItem::setArranger(const QString &arranger)
{
    if (m_arranger == arranger) return;

    m_arranger = arranger;
    emit arrangerChanged(arranger);
}

QString AbstractScorePropertiesItem::year() const
{
    return m_year;
}

void AbstractScorePropertiesItem::setYear(const QString &year)
{
    if (m_year == year) return;

    m_year = year;
    emit yearChanged(year);
}

QString AbstractScorePropertiesItem::copyright() const
{
    return m_copyright;
}

void AbstractScorePropertiesItem::setCopyright(const QString &copyright)
{
    if (m_copyright == copyright) return;

    m_copyright = copyright;
    emit copyrightChanged(copyright);
}

TimeSignature AbstractScorePropertiesItem::timeSignature() const
{
    return m_timeSignature;
}

void AbstractScorePropertiesItem::setTimeSignature(const TimeSignature &timeSig)
{
    if (m_timeSignature == timeSig) return;

    m_timeSignature = timeSig;
    emit timeSignatureChanged(timeSig);
}
