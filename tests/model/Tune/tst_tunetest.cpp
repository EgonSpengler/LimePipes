/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <tune.h>

class TuneTest : public QObject
{
    Q_OBJECT
    
public:
    TuneTest() : m_tune(0) {}
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testType();
    void testChildType();

private:
    Tune *m_tune;
};

void TuneTest::init()
{
    m_tune = new Tune();
}

void TuneTest::cleanup()
{
    delete m_tune;
}

void TuneTest::testType()
{
    QVERIFY2( m_tune->type() == MusicItem::Tune, "Tune returns the wrong type");
}

void TuneTest::testChildType()
{
    QVERIFY2( m_tune->childType() == MusicItem::Symbol, "The child itemtype of tune is not Symbol type");
}

QTEST_APPLESS_MAIN(TuneTest)

#include "tst_tunetest.moc"
