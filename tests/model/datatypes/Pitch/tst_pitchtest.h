/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */
#ifndef __PITCHTEST_H__
#define __PITCHTEST_H__

#include <QObject>
#include <src/model/datatypes/pitch.h>

class PitchTest : public QObject
{
    Q_OBJECT
    
public:
    PitchTest();
    
private Q_SLOTS:
    void testCreatePitch();
    void testSetPitchAsQVariant();
    void testName();
    void testStaffPos();
};

#endif
