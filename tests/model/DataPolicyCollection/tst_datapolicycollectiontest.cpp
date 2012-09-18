/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>

#include <datapolicycollection.h>
#include <itemdatatypes.h>

class DataPolicyCollectionTest : public QObject
{
    Q_OBJECT
    
public:
    DataPolicyCollectionTest()
        : m_collection(0) {}
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testSetGetPolicy();

private:
    DataPolicyCollection *m_collection;
};

void DataPolicyCollectionTest::init()
{
    m_collection = new DataPolicyCollection();
    m_collection->setPolicy(LP::scoreTitle, DataPolicy(DataPolicy::Read, 123));
}

void DataPolicyCollectionTest::cleanup()
{
    delete m_collection;
}

void DataPolicyCollectionTest::testSetGetPolicy()
{
    m_collection->setPolicy(LP::tuneInstrument, DataPolicy(DataPolicy::ReadWrite, 555));
    DataPolicy policy = m_collection->policyForRole(LP::tuneInstrument);
    QVERIFY2(policy.proxyRole() == 555, "Failed setting data policy");
    QVERIFY2(policy.isReadable() == true, "Policy isn't readable");
    QVERIFY2(policy.isWritable() == true, "Policy isn't writable");
}

QTEST_APPLESS_MAIN(DataPolicyCollectionTest)

#include "tst_datapolicycollectiontest.moc"
