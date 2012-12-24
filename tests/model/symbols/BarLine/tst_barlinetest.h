/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef BARLINETEST_H
#define BARLINETEST_H

#include <QObject>
#include <symbols/barline.h>

class BarLineTest : public QObject
{
    Q_OBJECT

public:
    BarLineTest()
        : m_bar(0) {}

private Q_SLOTS:
    void init();
    void cleanup();
    void testConstructor();
    void testBarSymbolType();
    void testWritingOfData();
    void testRepeat();
    void testWriteItemDataToStream();
    void testReadItemFromStream();

private:
    void readString(const QString &string);
    BarLine *m_bar;
};

#endif

