/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TUNETEST_H
#define TUNETEST_H

#include <QObject>
#include <tune.h>

class TuneTest : public QObject
{
    Q_OBJECT
    
public:
    TuneTest()
        : m_tune(0) {}
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testConstructor();
    void testType();
    void testChildType();
    void testOkToInsertChildRedefinition();
    void testSetData();
    void testWriteToXmlStream();

private:
    Tune *m_tune;
    InstrumentPtr m_instrument;
};

#endif
