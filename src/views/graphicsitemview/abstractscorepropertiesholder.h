/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ABSTRACTSCOREPROPERTIESHOLDER_H
#define ABSTRACTSCOREPROPERTIESHOLDER_H

#include <QObject>
#include <datatypes/timesignature.h>
#include "scorepropertiesinterface.h"

class AbstractScorePropertiesHolder : public QObject
{
    Q_OBJECT
public:
    explicit AbstractScorePropertiesHolder(QObject *parent = 0);
    virtual ~AbstractScorePropertiesHolder() {}

    void setScoreProperties(ScorePropertiesInterface *scoreProperties);
    ScorePropertiesInterface *scoreProperties() const;

public slots:
    virtual void setNewTitle(const QString& title) = 0;
    virtual void setNewComposer(const QString& composer) = 0;
    virtual void setNewArranger(const QString& arranger) = 0;
    virtual void setNewYear(const QString& year) = 0;
    virtual void setNewCopyright(const QString& copyright) = 0;
    virtual void setNewTimeSignature(const TimeSignature& timeSig) = 0;

private:
    ScorePropertiesInterface *m_scoreProperties;
};

#endif // ABSTRACTSCOREPROPERTIESHOLDER_H
