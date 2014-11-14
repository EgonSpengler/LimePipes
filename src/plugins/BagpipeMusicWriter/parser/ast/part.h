/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PART_H
#define PART_H

#include "musicitem.h"

class Part : public MusicItem
{
public:
    explicit Part(MusicItem *parent=0);

    void accept(AstVisitorInterface *visitor);
};

#endif // PART_H
