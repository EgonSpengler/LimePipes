/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCORE_H
#define SCORE_H

#include <QString>
#include <musicitem.h>
#include <itemdatatypes.h>

class Score : public MusicItem
{
public:
    explicit Score()
        : MusicItem(MusicItem::ScoreType, MusicItem::TuneType) {}
    explicit Score(const QString &title)
        : MusicItem(MusicItem::ScoreType, MusicItem::TuneType)
        { setTitle(title); }

    void setTitle(const QString &title);
    QString title() const
        { return data(LP::scoreTitle).toString(); }  
    bool itemSupportsWritingOfData(int role) const;
};

#endif // SCORE_H
