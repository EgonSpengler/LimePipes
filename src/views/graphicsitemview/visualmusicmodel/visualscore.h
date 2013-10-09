/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALSCORE_H
#define VISUALSCORE_H

#include "../scorepropertiesitem.h"
#include "../visualscoreinterface.h"
#include "abstractvisualitem.h"

class VisualScore : public VisualScoreInterface,
                    public AbstractVisualItem,
                    public ScorePropertiesItem
{
public:
    explicit VisualScore(QObject *parent = 0);

    // AbstractVisualItem interface
    Type type() const;
    void setDataFromIndex(const QPersistentModelIndex &index);

    // VisualScoreInterface interface
    GraphicalScoreInterface *graphicalScore() const;
    void setGraphicalScore(GraphicalScoreInterface *graphicalScore);

    // AbstractScorePropertiesItem interface
    void setNewTitle(const QString &title);
    void setNewComposer(const QString &composer);
    void setNewArranger(const QString &arranger);
    void setNewYear(const QString &year);
    void setNewCopyright(const QString &copyright);
    void setNewTimeSignature(const TimeSignature &timeSig);

private:
    GraphicalScoreInterface *m_graphicalScore;
};

#endif // VISUALSCORE_H
