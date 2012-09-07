/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef BAR_H
#define BAR_H

#include <QCoreApplication>

#include <symbol.h>

class Bar : public Symbol
{
    Q_DECLARE_TR_FUNCTIONS(Bar)
public:
    explicit Bar()
        : Symbol(LP::Bar,  tr("Bar")) {}
};

#endif // BAR_H
