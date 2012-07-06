/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "tunetest.h"
#include "tune.h"
#include "bar.h"

void TuneTest::testType()
{
    Tune tune;
    QVERIFY2( tune.type() == TuneType, "Tune returns the wrong type");
}

void TuneTest::testInsertSymbols()
{
    QStandardItemModel model;  //
    Tune tune;
    model.appendRow(&tune);
    QList<Symbol *> symbolList;
    symbolList << new Symbol() << new Symbol() << new Symbol() << new Symbol() ;

    // Insertion
    tune.insertSymbols(symbolList, QModelIndex());
    QVERIFY2( tune.rowCount() == 4, "Failed inserting symbols");

    // Appending
    symbolList.clear();
    symbolList << new Bar();
    tune.insertSymbols( symbolList, QModelIndex() );
    QVERIFY2( tune.child(tune.rowCount()-1)->type() == BarType, "Failed append symbol");

    // Insert somewhere in the middle
    symbolList.clear();
    symbolList << new Bar() << new Bar();
    int insertIdx = 1;

    QModelIndex ch_index = tune.child(insertIdx)->index();
    QVERIFY2( ch_index.isValid(), "No valid ModelIndex");

    tune.insertSymbols( symbolList, ch_index);
    QVERIFY2( tune.child(insertIdx)->type() == BarType, "Failed insert symbols in the middle (1)" );
    QVERIFY2( tune.child(insertIdx+1)->type() == BarType, "Failed insert symbols in the middle (2)" );
}
