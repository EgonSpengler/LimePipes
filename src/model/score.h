/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCORE_H
#define SCORE_H

#include <musicitem.h>
#include <itemdatatypes.h>

class Score : public MusicItem
{
public:
    explicit Score()
        : MusicItem(MusicItem::ScoreType, MusicItem::TuneType) {}
    Score(const QString &title)
        : MusicItem(MusicItem::ScoreType, MusicItem::TuneType)
        { setTitle(title); }
    QVariant data(int role) const;
    void setData(const QVariant &value, int role);

    void setTitle(const QString &title);
    QString title() const
        { return data(LP::scoreTitle).toString(); }

private:
    int mergeDoubleRoles(int role) const;
    bool isRoleAccepted(int role) const;
};

#endif // SCORE_H
