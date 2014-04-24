/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MELODYNOTEGLYPHITEM_H
#define MELODYNOTEGLYPHITEM_H

#include <common/graphictypes/glyphitem.h>
#include <common/datatypes/length.h>

class MelodyNoteGlyphItem : public GlyphItem
{
public:
    explicit MelodyNoteGlyphItem();

    void setLength(Length::Value length);

    // GlyphItem interface
protected:
    void smuflHasChanged(const SMuFLPtr &smufl);

private:
    QString noteheadForLength(Length::Value length);
    GlyphItem *m_notehead;
};

#endif // MELODYNOTEGLYPHITEM_H
