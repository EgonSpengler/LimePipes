/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCOREPROPERTIESHOLDERDUMMY_H
#define SCOREPROPERTIESHOLDERDUMMY_H

#include <graphicsitemview/abstractscorepropertiesholder.h>

class ScorePropertiesHolderDummy : public AbstractScorePropertiesHolder
{
public:
    ScorePropertiesHolderDummy();

    // AbstractScorePropertiesHolder interface
public slots:
    void setNewTitle(const QString &title) { Q_UNUSED(title); }
    void setNewComposer(const QString &composer) { Q_UNUSED(composer); }
    void setNewArranger(const QString &arranger) { Q_UNUSED(arranger); }
    void setNewYear(const QString &year) { Q_UNUSED(year); }
    void setNewCopyright(const QString &copyright) { Q_UNUSED(copyright); }
    void setNewTimeSignature(const TimeSignature &timeSig) { Q_UNUSED(timeSig); }
};

#endif // SCOREPROPERTIESHOLDERDUMMY_H
