/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef BARTEST_H
#define BARTEST_H

#include <QObject>
#include "../autotest.h"

class BarTest : public QObject
{
    Q_OBJECT
private slots:
    void testType();
};

DECLARE_TEST( BarTest )

#endif // BARTEST_H
