/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TST_PARTTEST_H
#define TST_PARTTEST_H

#include <QObject>
#include <src/model/part.h>

class PartTest : public QObject
{
    Q_OBJECT

public:
    PartTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testType();
};

#endif // TST_PARTTEST_H
