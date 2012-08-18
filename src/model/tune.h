/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TUNE_H
#define TUNE_H

#include <QList>
#include "musicitem.h"
#include "model_itemtypes.h"
#include "symbol.h"

class Tune : public MusicItem
{
public:
    explicit Tune();
    int type() const { return TuneType; }
    int parentType() const { return ScoreType; }
};

#endif // TUNE_H
