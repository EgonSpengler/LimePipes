/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLGRAPHICBUILDER_H
#define SYMBOLGRAPHICBUILDER_H

#include <musicitem.h>
#include <model/datatypes/symbolgraphic.h>

class SymbolGraphicBuilder
{
public:
    explicit SymbolGraphicBuilder(MusicItem *item);
    virtual ~SymbolGraphicBuilder() {}

    SymbolGraphicPtr symbolGraphic() { return m_graphic; }

public slots:
    virtual void createPixmaps(qreal lineHeight) = 0;
    virtual void updateSymbolGraphic() = 0;
    virtual bool isSymbolGraphicAffectedByDataRole(int role) = 0;

protected:
    QVariant itemData(int role) { return m_item->data(role); }
    void setSymbolGraphicPixmap(const QPixmap &pixmap) { m_graphic->setPixmap(pixmap); }
    void setSymbolGraphicYOffset(qreal yOffset) { m_graphic->setYOffset(yOffset); }

private:
    void initSymbolGraphic();
    MusicItem *m_item;
    SymbolGraphicPtr m_graphic;
};

#endif // SYMBOLGRAPHICBUILDER_H
