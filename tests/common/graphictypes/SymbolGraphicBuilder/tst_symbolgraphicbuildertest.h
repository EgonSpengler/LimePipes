/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLGRAPHICBUILDERTEST_H
#define SYMBOLGRAPHICBUILDERTEST_H

#include <QObject>
#include <testsymbolgraphicbuilder.h>
#include <src/common/graphictypes/symbolgraphicbuilder.h>

class SymbolGraphicBuilderTest : public QObject
{
    Q_OBJECT

public:
    SymbolGraphicBuilderTest() {}

private Q_SLOTS:
    void init();
    void cleanup();
    void testConstructor();
    void testSetGetData();
    void testUpdateSymbolGrapicCall();
    void testUpdateSymbolGraphicCallOnNonDependentBuilder();
    void testSetGetPixmap();
    void testSetYOffset();

private:
    TestSymbolGraphicBuilder *m_builder;
};

#endif
