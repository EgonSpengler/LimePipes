/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TIEGRAPHICBUILDER_H
#define TIEGRAPHICBUILDER_H

#include <QVector>
#include <QPersistentModelIndex>

#include <common/graphictypes/symbolgraphicbuilder.h>
#include <common/defines.h>

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
    SymbolSpanType m_spanType;
    QPersistentModelIndex m_buddyIndex;
    QVector<int> m_dataRoles;
};

#endif // TIEGRAPHICBUILDER_H
