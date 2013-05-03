/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MEASURE_H
#define MEASURE_H

#include <musicitem.h>

class Measure : public MusicItem
{
public:
    Measure(MusicItem *parent=0);
};

#endif // MEASURE_H
