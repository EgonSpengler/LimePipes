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
    
private Q_SLOTS:
    void testInsertRows();
    void testQAbstractItemModelImplementation();
};

MusicModelTest::MusicModelTest()
{
}

void MusicModelTest::testInsertRows()
{
    MusicModel *model = new MusicModel(this);
    QVERIFY2(model->insertRows(0, 1, QModelIndex()), "Failed inserting rows");
    QVERIFY2(model->rowCount(QModelIndex()) == 1, "Row was not inserted");
    QVERIFY2(model->insertRows(0, 3, QModelIndex()), "Failed inserting more rows");
    QVERIFY2(model->rowCount(QModelIndex()) == 4, "Rows weren't inserted");

    QModelIndex index1 = model->index(2, 0, QModelIndex());
    QVERIFY2(model->insertRows(0, 4, index1), "Failed inserting childrows");
    QVERIFY2(model->rowCount(index1) == 4, "Rows weren't inserted");
    delete model;
}

void MusicModelTest::testQAbstractItemModelImplementation()
{
    MusicModel *musicModel = new MusicModel(this);

    musicModel->insertRows(0, 3, QModelIndex()); // 3 top level items
    QModelIndex indexTop1 = musicModel->index(1, 0, QModelIndex());
    musicModel->setData(indexTop1, "indexTop1", Qt::DisplayRole);

    musicModel->insertRows(0, 4, indexTop1);  // 4 child items under the second top level item
    musicModel->setData( musicModel->index(0, 0, indexTop1), "child1", Qt::DisplayRole );
    musicModel->setData( musicModel->index(1, 0, indexTop1), "child2", Qt::DisplayRole );
    musicModel->setData( musicModel->index(2, 0, indexTop1), "child3", Qt::DisplayRole );
    musicModel->setData( musicModel->index(3, 0, indexTop1), "child4", Qt::DisplayRole );

    QModelIndex indexChild2 = musicModel->index(2, 0, indexTop1);
    musicModel->setData(indexChild2, "Childname", Qt::DisplayRole);
    QVERIFY2(musicModel->data(indexChild2, Qt::DisplayRole) == "Childname", "Failed setting data for a child");

    new ModelTest(musicModel, this);

    delete musicModel;
}

QTEST_APPLESS_MAIN(MusicModelTest)

#include "tst_musicmodeltest.moc"
