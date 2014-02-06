/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */
#ifndef __PITCHCONTEXTTEST_H__
#define __PITCHCONTEXTTEST_H__

#include <QObject>
#include <src/common/datatypes/pitchcontext.h>

class PitchContextTest : public QObject
{
    Q_OBJECT

public:
    PitchContextTest()
        :m_context(0) {}

private Q_SLOTS:
    void init();
    void cleanup();
    void testDefaultConstructor();
    void testLowestStaffPos();
    void testHighestStaffPos();
    void testPitchNames();
    void testPitchForName();
    void testPitchForStaffPos();

private:
    PitchContext *m_context;
};

#endif
