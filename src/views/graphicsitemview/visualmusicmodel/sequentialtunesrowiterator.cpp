/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "sequentialtunesrowiterator.h"

SequentialTunesRowIterator::SequentialTunesRowIterator(const VisualMusicModel *model,
                                                       const QModelIndex &scoreIndex)
    : RowIterator(model)
{
}
