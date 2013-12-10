/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <views/graphicsitemview/visualmusicmodel/sequentialtunesrowiterator.h>
#include <views/graphicsitemview/visualmusicmodel/visualmusicmodel.h>
#include <views/graphicsitemview/visualmusicmodel/visualitemfactory.h>

class SequentialTunesRowIteratorTest : public QObject
{
    Q_OBJECT

public:
    SequentialTunesRowIteratorTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testRowSequence();

private:
    SequentialTunesRowIterator *rowIterator;
};

SequentialTunesRowIteratorTest::SequentialTunesRowIteratorTest()
{
}

void SequentialTunesRowIteratorTest::init()
{
}

void SequentialTunesRowIteratorTest::cleanup()
{
}

void SequentialTunesRowIteratorTest::testRowSequence()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(SequentialTunesRowIteratorTest)

#include "tst_sequentialtunesrowiteratortest.moc"
