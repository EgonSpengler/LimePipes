/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TUNE_H
#define TUNE_H

#include <QStandardItem>
#include "model.h"

class Tune : public QStandardItem
{
public:
    explicit Tune();
    int type() const { return Model::TuneType; }

signals:

public slots:

};

#endif // TUNE_H
