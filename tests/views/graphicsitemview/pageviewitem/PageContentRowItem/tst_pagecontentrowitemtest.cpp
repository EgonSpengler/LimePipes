/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <QCoreApplication>
#include "tst_pagecontentrowitemtest.h"

PageContentRowItemTest::PageContentRowItemTest()
    : m_rowItem(0)
{
}

void PageContentRowItemTest::init()
{
    m_rowItem = new PageContentRowItem();
}

void PageContentRowItemTest::cleanup()
{
    delete m_rowItem;
}

void PageContentRowItemTest::testDefaultRow()
{
    QVERIFY2(m_rowItem->sizePolicy().verticalPolicy() == QSizePolicy::Fixed, "Vertical policy is not correct");
    QVERIFY2(m_rowItem->sizePolicy().horizontalPolicy() == QSizePolicy::MinimumExpanding, "Horizontal policy is not correct");
    QVERIFY2(m_rowItem->preferredHeight() > 0, "Default size is not greater than 0");
    QVERIFY2(m_rowItem->geometry().isValid(), "No valid geometry");
}

QTEST_MAIN(PageContentRowItemTest)
