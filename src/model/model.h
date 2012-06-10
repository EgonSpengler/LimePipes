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
    /*!
      @brief Inserts Tunes into the model.
      @param tunes The tunes to insert
      @param index The ModelIndex before the Symbols will be inserted.
         If index is invalid, the symbols will be appended to the list of symbols.
     */
    void insertTunes(QList<Tune *> tunes, const QModelIndex &index);

signals:

public slots:

};

#endif // MODEL_H
