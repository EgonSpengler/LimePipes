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
    void testParentType();

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
    QVERIFY2( m_tune->type() == TuneType, "Tune returns the wrong type");
}

void TuneTest::testParentType()
{
    QVERIFY2( m_tune->parentType() == ScoreType, "The parent itemtype of tune is not ScoreType");
}

QTEST_APPLESS_MAIN(TuneTest)

#include "tst_tunetest.moc"
