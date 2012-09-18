/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>

#include <datapolicy.h>

class DataPolicyTest : public QObject
{
    Q_OBJECT
    
public:
    DataPolicyTest()
        : m_dataPolicyRead(0), m_dataPolicyWrite(0), m_dataPolicyReadWrite(0) {}

private Q_SLOTS:
    void init();
    void cleanup();
    void testDefaultConstructor();
    void testIsReadable();
    void testIsWritable();
    void testProxyRole();
    void testGetProxyRole();

private:
    DataPolicy *m_dataPolicyRead;
    DataPolicy *m_dataPolicyWrite;
    DataPolicy *m_dataPolicyReadWrite;
};

void DataPolicyTest::init()
{
    m_dataPolicyRead = new DataPolicy(DataPolicy::Read);
    m_dataPolicyWrite = new DataPolicy(DataPolicy::Write);
    m_dataPolicyReadWrite = new DataPolicy(DataPolicy::ReadWrite);
}

void DataPolicyTest::cleanup()
{
    delete m_dataPolicyRead;
    delete m_dataPolicyWrite;
    delete m_dataPolicyReadWrite;
}

void DataPolicyTest::testDefaultConstructor()
{
    delete m_dataPolicyRead;
    m_dataPolicyRead = new DataPolicy();
    QVERIFY2(m_dataPolicyRead->isReadable() == false, "Failed, default data policy is readable");
    QVERIFY2(m_dataPolicyRead->isWritable() == false, "Failed, default data policy is writable");
}

void DataPolicyTest::testIsReadable()
{
    QVERIFY2(m_dataPolicyReadWrite->isReadable() == true, "Failed setting access in constructor with read write");
    QVERIFY2(m_dataPolicyRead->isReadable() == true, "Failed setting access in constructor with read only");
    QVERIFY2(m_dataPolicyWrite->isReadable() == false, "Failed setting access in constructor with write only");
}

void DataPolicyTest::testIsWritable()
{
    QVERIFY2(m_dataPolicyReadWrite->isWritable() == true, "Failed setting access in constructor with read write");
    QVERIFY2(m_dataPolicyRead->isWritable() == false, "Failed setting access in constructor with read only");
    QVERIFY2(m_dataPolicyWrite->isWritable() == true, "Failed setting access in constructor with write only");
}

void DataPolicyTest::testProxyRole()
{
    QVERIFY2(m_dataPolicyRead->hasProxyRole() == false, "Failed. DataRule has a proxy role although it isn't set in constructor");
    delete m_dataPolicyRead;
    m_dataPolicyRead = new DataPolicy(DataPolicy::Read, 12);
    QVERIFY2(m_dataPolicyRead->hasProxyRole() == true, "Failed setting proxy role through constructor");
}

void DataPolicyTest::testGetProxyRole()
{
    QVERIFY2(m_dataPolicyRead->proxyRole() == DataPolicy::NoProxyRole, "Default DataRule hasn't set NoProxyRole");
    delete m_dataPolicyRead;
    m_dataPolicyRead = new DataPolicy(DataPolicy::Read, 123);
    QVERIFY2(m_dataPolicyRead->proxyRole() == 123, "Failed setting proxy role in constructor");
}

QTEST_APPLESS_MAIN(DataPolicyTest)

#include "tst_datapolicytest.moc"
