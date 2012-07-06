/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "model.h"
#include "tune.h"

Model::Model(QObject *parent) :
    QStandardItemModel(parent)
{
    setColumnCount(2);
}
