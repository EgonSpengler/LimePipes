/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALMEASURE_H
#define VISUALMEASURE_H

#include <QObject>
#include "visualitem.h"

class VisualMeasure : public VisualItem
{
public:
    explicit VisualMeasure(QObject *parent = 0);
};

#endif // VISUALMEASURE_H
