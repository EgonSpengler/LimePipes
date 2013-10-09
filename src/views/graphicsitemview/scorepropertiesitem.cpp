/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "scorepropertiesitem.h"

ScorePropertiesItem::ScorePropertiesItem(QObject *parent)
    : QObject(parent),
      m_linkedItem(0)
{
    qRegisterMetaType<TimeSignature>("TimeSignature");
}

void ScorePropertiesItem::linkWithItem(ScorePropertiesItem *item)
{
    // Title
    connect(this, SIGNAL(titleChanged(QString)),
            item, SLOT(setTitle(QString)));
    connect(item, SIGNAL(titleChanged(QString)),
            this, SLOT(setTitle(QString)));
    // Composer
    connect(this, SIGNAL(composerChanged(QString)),
            item, SLOT(setComposer(QString)));
    connect(item, SIGNAL(composerChanged(QString)),
            this, SLOT(setComposer(QString)));
    // Arranger
    connect(this, SIGNAL(arrangerChanged(QString)),
            item, SLOT(setArranger(QString)));
    connect(item, SIGNAL(arrangerChanged(QString)),
            this, SLOT(setArranger(QString)));
    // Year
    connect(this, SIGNAL(yearChanged(QString)),
            item, SLOT(setYear(QString)));
    connect(item, SIGNAL(yearChanged(QString)),
            this, SLOT(setYear(QString)));
    // Copyright
    connect(this, SIGNAL(copyrightChanged(QString)),
            item, SLOT(setCopyright(QString)));
    connect(item, SIGNAL(copyrightChanged(QString)),
            this, SLOT(setCopyright(QString)));
    // Time signature
    connect(this, SIGNAL(timeSignatureChanged(TimeSignature)),
            item, SLOT(setTimeSignature(TimeSignature)));
    connect(item, SIGNAL(timeSignatureChanged(TimeSignature)),
            this, SLOT(setTimeSignature(TimeSignature)));
}

QString ScorePropertiesItem::title() const
{
    return m_title;
}

void ScorePropertiesItem::setTitle(const QString &title)
{
    if (m_title == title) return;

    m_title = title;
    emit titleChanged(title);
}

QString ScorePropertiesItem::composer() const
{
    return m_composer;
}

void ScorePropertiesItem::setComposer(const QString &composer)
{
    if (m_composer == composer) return;

    m_composer = composer;
    emit composerChanged(composer);
}


QString ScorePropertiesItem::arranger() const
{
    return m_arranger;
}

void ScorePropertiesItem::setArranger(const QString &arranger)
{
    if (m_arranger == arranger) return;

    m_arranger = arranger;
    emit arrangerChanged(arranger);
}

QString ScorePropertiesItem::year() const
{
    return m_year;
}

void ScorePropertiesItem::setYear(const QString &year)
{
    if (m_year == year) return;

    m_year = year;
    emit yearChanged(year);
}

QString ScorePropertiesItem::copyright() const
{
    return m_copyright;
}

void ScorePropertiesItem::setCopyright(const QString &copyright)
{
    if (m_copyright == copyright) return;

    m_copyright = copyright;
    emit copyrightChanged(copyright);
}

TimeSignature ScorePropertiesItem::timeSignature() const
{
    return m_timeSignature;
}

void ScorePropertiesItem::setTimeSignature(const TimeSignature &timeSig)
{
    if (m_timeSignature == timeSig) return;

    m_timeSignature = timeSig;
    emit timeSignatureChanged(timeSig);
}
