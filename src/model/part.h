/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PART_H
#define PART_H

#include <QStandardItem>
#include "model.h"

class Part : public QStandardItem
{
public:
    explicit Part();
    int type() const { return Model::PartType; }

signals:

public slots:

};

#endif // PART_H
