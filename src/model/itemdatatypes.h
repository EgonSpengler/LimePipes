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

    // Datatypes for Score
    scoreTitle = Qt::UserRole + 1,
    scoreComposer,
    scoreArranger,
    scoreYear,
    scoreCopyright,
    scoreTimeSignature,

    // Datatypes for Tune
    tuneInstrument,

    // Datatypes for Symbol
    symbolType,
    symbolLength
};

}

#endif // ITEMDATATYPES_H
