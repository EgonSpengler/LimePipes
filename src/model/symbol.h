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
#include <common/itemdataroles.h>
#include <common/datatypes/pitch.h>
#include <common/datatypes/length.h>

class SymbolBehavior;

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

    int symbolType() const;

    bool hasPitch() const;
    Pitch pitch() const;

    bool hasLength() const;
    Length::Value length() const;

    bool itemSupportsWritingOfData(int role) const;
    void writeItemDataToXmlStream(QXmlStreamWriter *writer);
    void readCurrentElementFromXmlStream(QXmlStreamReader *reader);

    SymbolBehavior *symbolBehavior() const;
    void setSymbolBehavior(SymbolBehavior *symbolBehavior);

protected:
    void setSymbolOptions(Symbol::Options options);

private:
    void setDefaultSymbolOptions();
    void writePitch(QXmlStreamWriter *writer);
    void writeLength(QXmlStreamWriter *writer);
    Symbol::Options m_symbolOptions;
    SymbolBehavior *m_behavior;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Symbol::Options)

#endif // SYMBOL_H
