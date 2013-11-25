/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALTUNE_H
#define VISUALTUNE_H

#include <QObject>
#include "visualitem.h"

class VisualTune : public VisualItem
{
public:
    explicit VisualTune(QObject *parent = 0);
};

#endif // VISUALTUNE_H
