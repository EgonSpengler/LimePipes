/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MODEL_H
#define MODEL_H

#include <QStandardItemModel>

class Tune;

class Model : public QStandardItemModel
{
    Q_OBJECT
public:

    explicit Model(QObject *parent = 0);
};

#endif // MODEL_H
