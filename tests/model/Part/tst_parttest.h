/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TST_PARTTEST_H
#define TST_PARTTEST_H

#include <QObject>
#include <part.h>

class PartTest : public QObject
{
    Q_OBJECT

public:
    PartTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testType();
    void testItemSupportsWritingOfData();

private:
    Part *m_part;
};

#endif // TST_PARTTEST_H
