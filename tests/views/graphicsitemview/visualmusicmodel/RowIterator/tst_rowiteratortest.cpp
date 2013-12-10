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
#include <QGraphicsWidget>
#include <views/graphicsitemview/visualmusicmodel/rowiterator.h>
#include <views/graphicsitemview/visualmusicmodel/visualmusicmodel.h>
#include <views/graphicsitemview/visualmusicmodel/visualitemfactory.h>

class RowIteratorTest : public QObject
{
    Q_OBJECT

public:
    RowIteratorTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testVisualMusicModelConstructor();
    void testRowCount();
    void testRowAt();

private:
    RowIterator *m_rowIterator;
};

RowIteratorTest::RowIteratorTest()
{
}

void RowIteratorTest::init()
{
    m_rowIterator = new RowIterator();
}

void RowIteratorTest::cleanup()
{
    delete m_rowIterator;
}

void RowIteratorTest::testVisualMusicModelConstructor()
{
    VisualItemFactory *factory = new VisualItemFactory();
    VisualMusicModel *model = new VisualMusicModel(factory);
    delete m_rowIterator;
    m_rowIterator = new RowIterator(model);

    QVERIFY2(m_rowIterator->visualMusicModel == model, "Visual music model was not set in constructor");

    delete factory;
    delete model;
}

void RowIteratorTest::testRowCount()
{
    m_rowIterator->m_rowItems.append(new QGraphicsWidget());
    m_rowIterator->m_rowItems.append(new QGraphicsWidget());

    QVERIFY2(m_rowIterator->rowCount() == 2, "Wrong row count");

    qDeleteAll(m_rowIterator->m_rowItems);
}

void RowIteratorTest::testRowAt()
{
    QGraphicsWidget *testWidget = new QGraphicsWidget();
    m_rowIterator->m_rowItems.append(new QGraphicsWidget());
    m_rowIterator->m_rowItems.append(new QGraphicsWidget());
    m_rowIterator->m_rowItems.append(testWidget);
    m_rowIterator->m_rowItems.append(new QGraphicsWidget());

    QVERIFY2(m_rowIterator->rowAt(2) == testWidget, "Wrong row returned for position");

    qDeleteAll(m_rowIterator->m_rowItems);
}

QTEST_MAIN(RowIteratorTest)

#include "tst_rowiteratortest.moc"
