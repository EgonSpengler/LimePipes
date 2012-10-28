/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @enum LP::DataRole
  * All data roles used to set the data for @ref MusicItem "MusicItems".
  *
  * @var LP::DataRole LP::scoreCopyright
  * The copyright for a tune without the copy sign.
  */

#ifndef ITEMDATATYPES_H
#define ITEMDATATYPES_H

#include <Qt>

namespace LP {

/*! The various data roles */
enum DataRole {

    // Score
    scoreTitle = Qt::UserRole + 1,
    scoreComposer,
    scoreArranger,
    scoreYear,
    scoreCopyright,
    scoreTimeSignature,

    // Tune
    tuneInstrument,

    // Symbol
    symbolType,
    symbolName,
    symbolLength,
    symbolPitch,
    symbolGraphic,

    // MelodyNote
    melodyNoteDots
};

}

#endif // ITEMDATATYPES_H
