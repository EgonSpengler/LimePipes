/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "tune.h"
#include <QDebug>

Tune::Tune() :
    QStandardItem()
{
    setText("Tune");
}

void Tune::insertSymbols(QList<Symbol *> &symbols, const QModelIndex &index)
{
    Symbol *symbol;
    foreach( symbol, symbols ){
        insertSymbol(symbol, index);
    }
}

void Tune::insertSymbol(Symbol *symbol, const QModelIndex &index)
{
    QList<QStandardItem *> cols;
    cols << symbol;
    if(symbol->pitch() != 0){
        cols << symbol->pitch();
    }

    if( !index.isValid() ){
        appendRow(cols);
    } else {
        insertRow(index.row(), cols);
    }
}
