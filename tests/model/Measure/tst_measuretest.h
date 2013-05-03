/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TST_MEASURETEST_H
#define TST_MEASURETEST_H

#include <QObject>
#include <src/model/measure.h>

class MeasureTest : public QObject
{
    Q_OBJECT

public:
    MeasureTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testType();

private:
    Measure *m_measure;
};

#endif // TST_MEASURETEST_H
