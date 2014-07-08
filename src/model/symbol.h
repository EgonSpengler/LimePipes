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
    explicit Symbol(MusicItem *parent=0);
    explicit Symbol(int type, const QString &name, MusicItem *parent=0);
    virtual ~Symbol();

    int symbolType() const;

    bool hasPitch() const;
    Pitch pitch() const;

    bool hasLength() const;
    Length::Value length() const;

    bool itemSupportsWritingOfData(int role) const;

    SymbolBehavior *symbolBehavior() const;
    void setSymbolBehavior(SymbolBehavior *symbolBehavior);

private:
    SymbolBehavior *m_behavior;
};

#endif // SYMBOL_H
