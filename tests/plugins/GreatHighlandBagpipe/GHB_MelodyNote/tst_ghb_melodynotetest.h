/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GHB_MELODYNOTETEST_H
#define GHB_MELODYNOTETEST_H

#include <plugins/GreatHighlandBagpipe/ghb_melodynote.h>

class GHB_MelodyNoteTest : public QObject
{
    Q_OBJECT
    
public:
    GHB_MelodyNoteTest()
        : m_melody(0) {}
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testDefaultConstructor();

private:
    GHB_MelodyNote *m_melody;
};

#endif
