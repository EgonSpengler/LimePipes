/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */
#ifndef __TIMESIGNATURETEST_H__
#define __TIMESIGNATURETEST_H__

#include <QtCore/QString>
#include <QtTest/QtTest>

#include <QObject>
#include <src/common/datatypes/timesignature.h>

class TimeSignatureTest : public QObject
{
    Q_OBJECT

public:
    TimeSignatureTest();

private Q_SLOTS:
    void testBeatCount();
    void testBeatUnit();
    void testQVariant();
    void testSetSignature();
    void testWriteToXmlStream();
    void testReadFromXmlStream();
    void testToAndFromString();
};

#endif

