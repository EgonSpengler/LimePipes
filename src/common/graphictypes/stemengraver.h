/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef STEMENGRAVER_H
#define STEMENGRAVER_H

#include <QList>

class GlyphItem;

class StemEngraver
{
public:
    explicit StemEngraver();
    virtual ~StemEngraver() {}

    void insertGlyphItem(int index, GlyphItem *glyphItem);

    void removeGlyphItem(GlyphItem *glyphItem);

private:
    QList<GlyphItem*> m_glyphItems;
};

#endif // STEMENGRAVER_H
