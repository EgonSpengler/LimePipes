/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLTEST_H
#define SYMBOLTEST_H

#include <QObject>
#include <testsymbol.h>
#include <testgraphicbuilder.h>

class SymbolTest : public QObject
{
    Q_OBJECT

public:
    SymbolTest(): m_symbol(0) {}

private Q_SLOTS:
    void init();
    void cleanup();
    void testConstructor();
    void testType();
    void testChildType();
    void testSymbolType();
    void testHasPitch();
    void testHasLength();
    void testWriteToXmlStream();
    void testReadFromXmlStream();

private:
    void readTextElement(const QString &tagName, const QString &elementText);
    void readString(const QString &string);
    QString patternForTag(const QString &tagname, const QString &data);
    Symbol *m_symbol;
};

#endif

