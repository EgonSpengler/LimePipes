/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <QScopedPointer>
#include "pageviewdummy.h"
#include <graphicsitemview/visualmusicpresenter.h>

class VisualMusicPresenterTest : public QObject
{
    Q_OBJECT

public:
    VisualMusicPresenterTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testSetGetPageView();

private:
    PageViewDummy *m_pageView;
    VisualMusicPresenter *m_musicPresenter;
};

VisualMusicPresenterTest::VisualMusicPresenterTest()
{
}

void VisualMusicPresenterTest::init()
{
    m_pageView = new PageViewDummy();
    m_musicPresenter = new VisualMusicPresenter(this);
    m_musicPresenter->setPageView(m_pageView);
}

void VisualMusicPresenterTest::cleanup()
{
    delete m_musicPresenter;
}

void VisualMusicPresenterTest::testSetGetPageView()
{
    QScopedPointer<PageViewInterface> pageView(new PageViewDummy());
    m_musicPresenter->setPageView(pageView.data());
    QVERIFY2(m_musicPresenter->pageView() == pageView.data(), "Wrong page view returned by presenter");
}

QTEST_APPLESS_MAIN(VisualMusicPresenterTest)

#include "tst_visualmusicpresentertest.moc"
