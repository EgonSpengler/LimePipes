/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TESTSYMBOL_H
#define TESTSYMBOL_H

#include <symbol.h>
#include <QObject>

class TestSymbol : public QObject,
                   public Symbol
{
    Q_OBJECT
public:
    explicit TestSymbol(QObject *parent = 0);

protected:
    void afterWritingData(int role) { Q_UNUSED(role) emit afterWritingDataCalled(); }

signals:
    void afterWritingDataCalled();
};

#endif // TESTSYMBOL_H
