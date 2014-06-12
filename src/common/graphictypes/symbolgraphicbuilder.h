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
#include <QObject>
#include <common/graphictypes/MusicFont/musicfont.h>

class GlyphItem;

class SymbolGraphicBuilder : public QObject
{
    Q_OBJECT
    friend class SymbolGraphicBuilderTest;

public:
    explicit SymbolGraphicBuilder();
    virtual ~SymbolGraphicBuilder() {}

    /*!
     * \brief glyphItem Return the GlyphItem which represents the Symbol
     */
    virtual GlyphItem *glyphItem() const;

    void setData(const QVariant &value, int key);
    QVariant data(int key) const;

    MusicFontPtr musicFont() const { return m_musicFont; }
    void setMusicFont(const MusicFontPtr &musicFont)
    {
        m_musicFont = musicFont;
        musicFontChanged(m_musicFont);
    }

    /*! \brief graphicDataRoles Returns the data roles which affect the appearance of the graphic. */
    virtual QVector<int> graphicDataRoles() const
    {
        return QVector<int>();
    }

    int symbolType() const;
    void setSymbolType(int symbolType);

signals:
    void dataChanged(const QVariant& data, int role);

protected:
    virtual void updateSymbolGraphic(const QVariant& value, int key)
    {
        Q_UNUSED(value);
        Q_UNUSED(key);
    }

    virtual void musicFontChanged(const MusicFontPtr &musicFont) { Q_UNUSED(musicFont); }

private:
    QHash<int, QVariant> m_graphicData;
    MusicFontPtr m_musicFont;
    int m_symbolType;
};

#endif // SYMBOLGRAPHICBUILDER_H
