/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MELODYNOTE_H
#define MELODYNOTE_H

#include "../symbol.h"
#include "../pitch.h"
#include "../model_itemtypes.h"

class MelodyNote : public Symbol
{
public:
    explicit MelodyNote();
    ~MelodyNote();
    int type() const { return MelodyNoteType; }
    /*! @brief Adds a dot to the melody note. If it has already two dots,
      * it is resetted to zero dots.
      */
    void addDot();

    int dots() const;
    /*! @brief Sets the dots of the melody note.
      * @param dots Can only be of the value 0, 1 or 2. The dots are set to 2 if the value
      * is greater than 2 and it is set to 0 if it is lesser than 0.
      */
    void setDots( int dots );
    Pitch *pitch() const;

private:
    int m_dots;
    Pitch *m_pitch;
};

#endif // MELODYNOTE_H
