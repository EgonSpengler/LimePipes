#ifndef LENGTHTEST_H
#define LENGTHTEST_H

#include <QObject>
#include "../autotest.h"

class LengthTest : public QObject
{
    Q_OBJECT
public:
    explicit LengthTest(QObject *parent = 0);
    
private slots:
    void testCase1();
    
};

#endif // LENGTHTEST_H
