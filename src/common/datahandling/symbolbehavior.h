/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLBEHAVIOR_H
#define SYMBOLBEHAVIOR_H

#include <QFlags>

#include "itembehavior.h"

class SymbolBehavior : public ItemBehavior
{
public:
    enum SymbolOption {
        NoOption = 0x00,
        Pitch  = 0x01,
        Length = 0x02
    };
    Q_DECLARE_FLAGS(SymbolOptions, SymbolOption)

    SymbolBehavior();
    virtual ~SymbolBehavior() {}

    int symbolType() const;
    void setSymbolType(int type);

    SymbolOptions options() const;
    void setOptions(const SymbolOptions &options);
    bool hasOption(SymbolOption option);

private:
    SymbolOptions m_options;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(SymbolBehavior::SymbolOptions)

#endif // SYMBOLBEHAVIOR_H
