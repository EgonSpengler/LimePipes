/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PART_H
#define PART_H

#include <musicitem.h>

class Part : public MusicItem
{
public:
    Part(MusicItem *parent=0);
};

#endif // PART_H
