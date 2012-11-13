/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef BARLINE_H
#define BARLINE_H

#include <QCoreApplication>
#include <symbol.h>

class BarLine : public Symbol
{
    Q_DECLARE_TR_FUNCTIONS(Bar)
public:
    explicit BarLine();
};

#endif // BARLINE_H
