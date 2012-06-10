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
#include "model_itemtypes.h"
#include "symbol.h"

class Tune : public QStandardItem
{
public:
    explicit Tune();
    int type() const { return TuneType; }
    /*!
      @brief Inserts Symbols into the tune.
      @param symbols The symbols to insert
      @param index The ModelIndex before the Symbols will be inserted.
         If index is invalid, the symbols will be appended to the list of symbols.
     */
    void insertSymbols(QList<Symbol *> symbols, const QModelIndex& index);

signals:

public slots:

};

#endif // TUNE_H
