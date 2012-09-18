/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>

#include <datarule.h>

class DataRuleTest : public QObject
{
    Q_OBJECT
    
public:
    DataRuleTest()
        : m_dataRuleRead(0), m_dataRuleWrite(0), m_dataRuleReadWrite(0) {}
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testIsReadable();
    void testIsWritable();
    void testProxyRole();
    void testGetProxyRole();

private:
    DataRule *m_dataRuleRead;
    DataRule *m_dataRuleWrite;
    DataRule *m_dataRuleReadWrite;
};

void DataRuleTest::init()
{
    m_dataRuleRead = new DataRule(DataRule::Read);
    m_dataRuleWrite = new DataRule(DataRule::Write);
    m_dataRuleReadWrite = new DataRule(DataRule::ReadWrite);
}

void DataRuleTest::cleanup()
{
    delete m_dataRuleRead;
    delete m_dataRuleWrite;
    delete m_dataRuleReadWrite;
}

void DataRuleTest::testIsReadable()
{
    QVERIFY2(m_dataRuleReadWrite->isReadable() == true, "Failed setting access in constructor with read write");
    QVERIFY2(m_dataRuleRead->isReadable() == true, "Failed setting access in constructor with read only");
    QVERIFY2(m_dataRuleWrite->isReadable() == false, "Failed setting access in constructor with write only");
}

void DataRuleTest::testIsWritable()
{
    QVERIFY2(m_dataRuleReadWrite->isWritable() == true, "Failed setting access in constructor with read write");
    QVERIFY2(m_dataRuleRead->isWritable() == false, "Failed setting access in constructor with read only");
    QVERIFY2(m_dataRuleWrite->isWritable() == true, "Failed setting access in constructor with write only");
}

void DataRuleTest::testProxyRole()
{
    QVERIFY2(m_dataRuleRead->hasProxyRole() == false, "Failed. DataRule has a proxy role although it isn't set in constructor");
    delete m_dataRuleRead;
    m_dataRuleRead = new DataRule(DataRule::Read, 12);
    QVERIFY2(m_dataRuleRead->hasProxyRole() == true, "Failed setting proxy role through constructor");
}

void DataRuleTest::testGetProxyRole()
{
    QVERIFY2(m_dataRuleRead->proxyRole() == DataRule::NoProxyRole, "Default DataRule hasn't set NoProxyRole");
    delete m_dataRuleRead;
    m_dataRuleRead = new DataRule(DataRule::Read, 123);
    QVERIFY2(m_dataRuleRead->proxyRole() == 123, "Failed setting proxy role in constructor");
}

QTEST_APPLESS_MAIN(DataRuleTest)

#include "tst_dataruletest.moc"
