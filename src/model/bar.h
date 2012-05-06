/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef BAR_H
#define BAR_H

#include <QStandardItem>
#include "model.h"

class Bar : public QStandardItem
{
public:
    explicit Bar();
    int type() const { return Model::BarType; }

signals:

public slots:

};

#endif // BAR_H
