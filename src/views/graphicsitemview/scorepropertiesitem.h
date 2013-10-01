/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCOREPROPERTIESITEM_H
#define SCOREPROPERTIESITEM_H

#include <QObject>
#include <QString>
#include "scorepropertiesinterface.h"

class ScorePropertiesItem : public QObject,
                            public ScorePropertiesInterface
{
    Q_OBJECT
public:
    explicit ScorePropertiesItem(QObject *parent = 0);
    ~ScorePropertiesItem() {}

signals:
    void titleChanged(const QString& newTitle);
    void composerChanged(const QString& newComposer);
    void arrangerChanged(const QString& newArranger);
    void yearChanged(const QString& newYear);
    void copyrightChanged(const QString& newCopyright);
    void timeSignatureChanged(const TimeSignature& newTimeSignature);

    // ScorePropertiesInterface interface
public:
    QString title() const;
    void setTitle(const QString &title);
    QString composer() const;
    void setComposer(const QString &composer);
    QString arranger() const;
    void setArranger(const QString &arranger);
    QString year() const;
    void setYear(const QString &year);
    QString copyright() const;
    void setCopyright(const QString &copyright);
    TimeSignature timeSignature() const;
    void setTimeSignature(const TimeSignature &timeSig);

private:
    QString m_title;
    QString m_composer;
    QString m_arranger;
    QString m_year;
    QString m_copyright;
    TimeSignature m_timeSignature;
};

#endif // SCOREPROPERTIESITEM_H
