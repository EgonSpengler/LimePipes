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
#include <common/itemdataroles.h>

class Score : public MusicItem
{
public:
    explicit Score(MusicItem *parent=0);
    explicit Score(const QString &title);

    bool itemSupportsWritingOfData(int role) const;

private:
    void initItem();
    void setTitle(const QString &title);
};

#endif // SCORE_H
