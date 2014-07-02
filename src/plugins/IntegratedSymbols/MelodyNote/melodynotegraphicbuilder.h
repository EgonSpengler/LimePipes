/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MELODYNOTEGRAPHICBUILDER_H
#define MELODYNOTEGRAPHICBUILDER_H

#include <common/datatypes/pitch.h>
#include <common/graphictypes/symbolgraphicbuilder.h>
#include <common/datatypes/pitchcontext.h>

class MelodyNoteGlyphItem;

class MelodyNoteGraphicBuilder : public SymbolGraphicBuilder
{
public:
    explicit MelodyNoteGraphicBuilder();

    void updateSymbolGraphic(const QVariant &value, int key);
    QVector<int> graphicDataRoles() const;
    GlyphItem *glyphItem() const;
    void setPluginManager(const PluginManager &pluginManager);

private:
    bool isPitchOnLine(const Pitch &pitch) const;
    void setLedgerLinesForPitch(const Pitch &pitch);
    int ledgerLineCountForStaffPos(int staffPos);

    MelodyNoteGlyphItem *m_glyph;
    PitchContextPtr m_pitchContext;
    PluginManager m_pluginManager;
};

#endif // MELODYNOTEGRAPHICBUILDER_H
