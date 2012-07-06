/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCORETEST_H
#define SCORETEST_H

#include <QObject>
#include "../autotest.h"

class ScoreTest : public QObject
{
    Q_OBJECT
private slots:
    void testType();
};

DECLARE_TEST( ScoreTest )

#endif // SCORETEST_H
