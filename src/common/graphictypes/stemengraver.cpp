/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "glyphitem.h"
#include "stemengraver.h"

StemEngraver::StemEngraver()
{
}

void StemEngraver::insertGlyphItem(int index, GlyphItem *glyphItem)
{
    m_glyphItems.insert(index, glyphItem);
}

void StemEngraver::removeGlyphItem(GlyphItem *glyphItem)
{
    m_glyphItems.removeAll(glyphItem);
}
