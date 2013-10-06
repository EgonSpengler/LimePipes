/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ABSTRACTSCOREPROPERTIESITEM_H
#define ABSTRACTSCOREPROPERTIESITEM_H

#include <QObject>
#include <QString>
#include "scorepropertiesinterface.h"

class AbstractScorePropertiesItem : public QObject,
                                    public ScorePropertiesInterface
{
    Q_OBJECT
public:
    explicit AbstractScorePropertiesItem(QObject *parent = 0);
    ~AbstractScorePropertiesItem() {}

    void linkWithItem(AbstractScorePropertiesItem *item);

signals:
    void titleChanged(const QString& newTitle);
    void composerChanged(const QString& newComposer);
    void arrangerChanged(const QString& newArranger);
    void yearChanged(const QString& newYear);
    void copyrightChanged(const QString& newCopyright);
    void timeSignatureChanged(const TimeSignature& newTimeSignature);

public slots:
    virtual void setNewTitle(const QString& title) = 0;
    virtual void setNewComposer(const QString& composer) = 0;
    virtual void setNewArranger(const QString& arranger) = 0;
    virtual void setNewYear(const QString& year) = 0;
    virtual void setNewCopyright(const QString& copyright) = 0;
    virtual void setNewTimeSignature(const TimeSignature& timeSig) = 0;

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

#endif // ABSTRACTSCOREPROPERTIESITEM_H
