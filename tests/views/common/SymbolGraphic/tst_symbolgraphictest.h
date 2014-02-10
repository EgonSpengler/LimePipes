/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */
#ifndef __SYMBOLGRAPHICTEST_H__
#define __SYMBOLGRAPHICTEST_H__

#include <QObject>
#include <src/views/common/symbolgraphic.h>

class SymbolGraphicTest : public QObject
{
    Q_OBJECT

public:
    SymbolGraphicTest();

private Q_SLOTS:
    void testDefaultConstructor();
    void testConstructor();
    void testQVariant();
};

#endif
