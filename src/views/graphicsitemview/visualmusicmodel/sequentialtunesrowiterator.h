/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SEQUENTIALTUNESROWITERATOR_H
#define SEQUENTIALTUNESROWITERATOR_H

#include "rowiterator.h"

/*!
 * \brief The SequentialTunesRowIterator class
 *        Returns the row items of tunes in a score sequentially.
 */
class SequentialTunesRowIterator : public RowIterator
{
public:
    explicit SequentialTunesRowIterator(const VisualMusicModel *model,
                                        const QModelIndex& scoreIndex);
};

#endif // SEQUENTIALTUNESROWITERATOR_H
