/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICMODELTEST_H
#define MUSICMODELTEST_H

#include <QObject>
#include "../autotest.h"

class MusicModelTest : public QObject
{
    Q_OBJECT
private slots:
    void testCase1();
};

DECLARE_TEST( MusicModelTest )

#endif // MUSICMODELTEST_H
