/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOL_H
#define SYMBOL_H

#include <QCoreApplication>
#include <musicitem.h>
#include <itemdatatypes.h>
#include <datatypes/pitch.h>
#include <datatypes/length.h>
#include <symbolgraphicbuilder.h>
#include "../interfaces/interfaceglobals.h"

class Symbol : public MusicItem
{
    Q_DECLARE_TR_FUNCTIONS(MusicItem)
public:
    enum Option {
        NoOption =     0x00,
        HasPitch =     0x01,
        HasLength =    0x02
    };
    Q_DECLARE_FLAGS(Options, Option)

    explicit Symbol(MusicItem *parent=0);
    explicit Symbol(int type, const QString &name, MusicItem *parent=0);
    virtual ~Symbol();

    int symbolType() const { return data(LP::symbolType).toInt(); }

    bool hasPitch() const;
    PitchPtr pitch() const;

    bool hasLength() const;
    Length::Value length() const;

    bool hasGraphic() const;
    void createSymbolPixmaps(int lineHeight);

    bool itemSupportsWritingOfData(int role) const;
    void writeItemDataToXmlStream(QXmlStreamWriter *writer);
    void readCurrentElementFromXmlStream(QXmlStreamReader *reader);

protected:
    void setSymbolOptions(Symbol::Options options);
    void setSymbolGraphicBuilder(SymbolGraphicBuilder *builder);

private:
    void setDefaultSymbolOptions();
    void afterWritingData(int role);
    void writePitch(QXmlStreamWriter *writer);
    void writeLength(QXmlStreamWriter *writer);
    Symbol::Options m_symbolOptions;
    SymbolGraphicBuilder *m_graphicBuilder;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Symbol::Options)

#endif // SYMBOL_H
