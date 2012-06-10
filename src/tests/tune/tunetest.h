/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TUNETEST_H
#define TUNETEST_H

#include <QObject>
#include "../autotest.h"

class TuneTest : public QObject
{
    Q_OBJECT
private slots:
    void testType();
    void testInsertSymbols();
};

DECLARE_TEST( TuneTest )

#endif // TUNETEST_H
