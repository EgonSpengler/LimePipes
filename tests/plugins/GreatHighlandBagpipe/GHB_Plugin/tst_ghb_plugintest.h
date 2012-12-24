/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GHB_PLUGINTEST_H
#define GHB_PLUGINTEST_H

#include <plugins/GreatHighlandBagpipe/greathighlandbagpipe.h>


class GHB_PluginTest : public QObject
{
    Q_OBJECT
    
public:
    GHB_PluginTest()
        : m_bagpipe(0) {}
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testCreate();
    void testName();
    void testInstrumentID();
    void testsupportedSymbolTypes();
    void testSymbolNamesForAllSymbols();
    void testPitchContext();

private:
    GreatHighlandBagpipe *m_bagpipe;
};

#endif
