/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MODELTEST_H
#define MODELTEST_H

#include <QObject>
#include "../autotest.h"

class ModelTest : public QObject
{
    Q_OBJECT
private slots:
    void testCase1();
};

DECLARE_TEST( ModelTest )

#endif // MODELTEST_H
