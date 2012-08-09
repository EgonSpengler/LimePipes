#ifndef PITCHTEST_H
#define PITCHTEST_H

#include <QObject>
#include "../autotest.h"

class PitchTest : public QObject
{
    Q_OBJECT
public:
    explicit PitchTest(QObject *parent = 0);
    
private slots:
    void testCase1();
};

DECLARE_TEST( PitchTest )

#endif // PITCHTEST_H
