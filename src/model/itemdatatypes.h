/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ITEMDATATYPES_H
#define ITEMDATATYPES_H

#include <Qt>

namespace LP {

/*! The various data roles */
enum DataRole {

    // Datatypes for Score
    scoreTitle = Qt::UserRole + 1,  /*!< The title for a score (QString) */
    scoreComposer,                  /*!< The composer's name for a score (QString) */
    scoreArranger,                  /*!< The arranger's name for a score (QString) */
    scoreYear,                      /*!< The year of composing/arranging of the score (QString) */
    scoreCopyright,                 /*!< The copyright for a score without the copy sign (QString) */

    // Various data types
    timeSignature,      /*!< The time signature for a Tune for example (TimeSignature) */
    length,             /*!< The Symbol's length (Length) */
    instrument,         /*!< The instrument for a Tune (Instrument) */
    instrumentId        /*!< The instrument ID for symbols in a tune (int) */

    /* Not yet needed */
//    //* Standard Music-Sheet-Roles */
//    MusicSheetSymbol,   /*!< The appearance in the music sheet. (QIcon) */

//    //* Code roles */
//    LimePipesCode,  /*!< The LimePipesCode for the Symbol (QString) */
//    CustomCode      /*!< A custom Code appearance, e.g. BWW-code (QString) */
};

}

#endif // ITEMDATATYPES_H
