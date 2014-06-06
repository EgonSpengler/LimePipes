/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef STEMGLYPHITEM_H
#define STEMGLYPHITEM_H

#include <common/datatypes/length.h>

#include "glyphitem.h"

class StemGlyphItem : public GlyphItem
{
public:
    explicit StemGlyphItem();

    void setLength(Length::Value length);

private:
    GlyphItem *m_flag;
};

#endif // STEMGLYPHITEM_H
