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
