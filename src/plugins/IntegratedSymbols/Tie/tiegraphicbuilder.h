/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TIEGRAPHICBUILDER_H
#define TIEGRAPHICBUILDER_H

#include <common/graphictypes/symbolgraphicbuilder.h>

class TieGraphicBuilder : public SymbolGraphicBuilder
{
public:
    TieGraphicBuilder();

    // SymbolGraphicBuilder interface
public:
    QVector<int> graphicDataRoles() const;

protected:
    void updateSymbolGraphic(const QVariant &value, int key);
    void musicFontChanged(const MusicFontPtr &musicFont);

private:
    QVector<int> m_dataRoles;
};

#endif // TIEGRAPHICBUILDER_H
