/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLGRAPHICBUILDER_H
#define SYMBOLGRAPHICBUILDER_H

#include <QHash>
#include <QVector>
#include <QVariant>
#include "symbolgraphic.h"
#include "musicfont/musicfont.h"

class SymbolGraphicBuilder
{
    friend class SymbolGraphicBuilderTest;
public:
    explicit SymbolGraphicBuilder();
    virtual ~SymbolGraphicBuilder() {}

    SymbolGraphicPtr symbolGraphic() { return m_graphic; }

    void setStaffLineHeight(int staffLineHeight);
    int staffLineHeight() const;

    void setData(const QVariant &value, int key);
    QVariant data(int key) const;

    /*! \brief isGraphicValid Returns true, if all required data is set and valid */
    bool isGraphicValid() const;

protected:
    MusicFontPtr musicFont() { return s_musicFont; }

    void setSymbolGraphicPixmap(const QPixmap &pixmap);
    void setSymbolGraphicYOffset(qreal yOffset);

    /*! \brief dataChanged Will be called, if data has changed which is affects the graphic.
     *                    It will not be called before the first initSymbolGraphic call. */
    virtual void updateSymbolGraphic(const QVariant& value, int key)
    {
        Q_UNUSED(value);
        Q_UNUSED(key);
    }

    /*! \brief graphicDataRoles Returns the data roles which affect the appearance of the graphic. */
    virtual QVector<int> graphicDataRoles() const
    {
        return QVector<int>();
    }

    /*! \brief initSymbolGraphic Will be called if all required graphic data has been set. */
    virtual void initializeSymbolGraphic() {}

private:
    void initSymbolGraphicMember();
    void handleInitOfSymbolGraphic(const QVariant& value, int key);
    SymbolGraphicPtr m_graphic;
    bool m_graphicWasInitialized;
    QHash<int, QVariant> m_graphicData;
    static MusicFontPtr s_musicFont;
};

#endif // SYMBOLGRAPHICBUILDER_H
