/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "qt_modeltest/modeltest.h"
#include <musicmodel.h>

class MusicModelTest : public QObject
{
    Q_OBJECT
    
public:
    MusicModelTest();

public slots:
    void rowsInsertedNotifier() {
        // This slot will be connected with the rowsInserted Signal of the model
        // to check that items weren't inserted
        QVERIFY2(false, "Rows were inserted");
    }
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testInsertRows();
    void testQAbstractItemModelImplementation();
    void testItemForIndex();
    void testInsertNoItemType();

private:
    MusicModel *m_model;
};

MusicModelTest::MusicModelTest()
    : m_model(0)
{
}

void MusicModelTest::init()
{
    m_model = new MusicModel(this);
}

void MusicModelTest::cleanup()
{
    delete m_model;
}

void MusicModelTest::testInsertRows()
{
    QVERIFY2(m_model->insertRows(0, 1, QModelIndex()), "Failed inserting rows");
    QVERIFY2(m_model->rowCount(QModelIndex()) == 1, "Row was not inserted");
    QVERIFY2(m_model->insertRows(0, 3, QModelIndex()), "Failed inserting more rows");
    QVERIFY2(m_model->rowCount(QModelIndex()) == 4, "Rows weren't inserted");

    QModelIndex index1 = m_model->index(2, 0, QModelIndex());
    QVERIFY2(m_model->insertRows(0, 4, index1), "Failed inserting childrows");
    QVERIFY2(m_model->rowCount(index1) == 4, "Rows weren't inserted");
}

void MusicModelTest::testQAbstractItemModelImplementation()
{
    m_model->insertRows(0, 3, QModelIndex()); // 3 top level items
    QModelIndex indexTop1 = m_model->index(1, 0, QModelIndex());
    m_model->setData(indexTop1, "indexTop1", Qt::DisplayRole);

    m_model->insertRows(0, 4, indexTop1);  // 4 child items under the second top level item
    m_model->setData( m_model->index(0, 0, indexTop1), "child1", Qt::DisplayRole );
    m_model->setData( m_model->index(1, 0, indexTop1), "child2", Qt::DisplayRole );
    m_model->setData( m_model->index(2, 0, indexTop1), "child3", Qt::DisplayRole );
    m_model->setData( m_model->index(3, 0, indexTop1), "child4", Qt::DisplayRole );

    QModelIndex indexChild2 = m_model->index(2, 0, indexTop1);
    m_model->setData(indexChild2, "Childname", Qt::DisplayRole);
    QVERIFY2(m_model->data(indexChild2, Qt::DisplayRole) == "Childname", "Failed setting data for a child");

    ModelTest * modelTest = new ModelTest(m_model, this);
    delete modelTest;
}

void MusicModelTest::testItemForIndex()
{
    m_model->insertRows(0, 1, QModelIndex());
    QModelIndex mIndex = m_model->index(0, 0, QModelIndex());
    m_model->setData(mIndex, QString("hello there"), Qt::DisplayRole);
    QVERIFY2(m_model->itemForIndex(mIndex)->data(Qt::DisplayRole) == "hello there", "Failed to get the correct item for an index");
}

void MusicModelTest::testInsertNoItemType()
{
    // If in the hirarchy is a item with NoItemType as childType,
    // any attempt to insert child items should be canceled before the call of
    // beginInsertRows/endInsertRows, because this shouldn't be called, if the insertion will fail

    // Get the index with an item with NoItem as its child type
    QModelIndex index = QModelIndex();
    while (1) {
        m_model->insertRow(0, index);
        index = m_model->index(0, 0, index);

        MusicItem *item = static_cast<MusicItem*>(
                            index.internalPointer());
        if (item->childType() == MusicItem::NoItemType) {
            break;
        }
    }

    // Now, the rowsInserted signal should not be called when inserting rows
    QObject::connect(m_model, SIGNAL(rowsInserted(const QModelIndex, int, int)),
                     this, SLOT(rowsInsertedNotifier()));
    m_model->insertRow(0, index);
}

QTEST_APPLESS_MAIN(MusicModelTest)

#include "tst_musicmodeltest.moc"
