/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCORE_H
#define SCORE_H

#include <QStandardItem>
#include "model_itemtypes.h"

class Score : public QStandardItem
{
public:
    explicit Score();
    int type() const { return ScoreType; }

signals:

public slots:

};

#endif // SHEETMUSIC_H
