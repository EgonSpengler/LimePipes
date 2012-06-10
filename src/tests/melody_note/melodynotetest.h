#ifndef MELODYNOTETEST_H
#define MELODYNOTETEST_H

#include <QObject>
#include "../autotest.h"

class MelodyNoteTest : public QObject
{
    Q_OBJECT
private slots:
    void testType();
    void testDots();
};

DECLARE_TEST( MelodyNoteTest )

#endif // MELODYNOTETEST_H
