/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLTEST_H
#define SYMBOLTEST_H

#include <QObject>
#include "../autotest.h"

class SymbolTest : public QObject
{
    Q_OBJECT
private slots:
    void testType();
};

DECLARE_TEST( SymbolTest )

#endif // SYMBOLTEST_H
