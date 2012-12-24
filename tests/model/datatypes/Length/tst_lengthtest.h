/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */
#ifndef __LENGTHTEST_H__
#define __LENGTHTEST_H__

#include <QVariant>
#include <src/model/datatypes/length.h>

class LengthTest : public QObject
{
    Q_OBJECT
    
public:
    LengthTest();
    
private Q_SLOTS:
    void testValues();
    void testValueForName();
    void testNameForValue();
    void testSetLengthAsVariant();
    void testLengthNames();
    void testLengthValues();
};

#endif
