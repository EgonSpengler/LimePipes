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
}

void Tune::insertSymbols(QList<Symbol *> symbols, const QModelIndex &index)
{
    QList<QStandardItem *> itemList;
    Symbol *symbol;
    foreach( symbol, symbols ){
        itemList << static_cast<QStandardItem *>(symbol);
    }

    if( !index.isValid() ){
        appendRows(itemList);
    } else {
        insertRows(index.row(), itemList);
    }
}
