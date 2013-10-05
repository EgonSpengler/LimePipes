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
#include <QStandardItemModel>
#include "pageviewdummy.h"
#include <model/musicmodel.h>
#include <graphicsitemview/visualmusicpresenter.h>
#include <graphicsitemview/visualmusicmodel/visualmusicmodel.h>

Q_IMPORT_PLUGIN(lp_greathighlandbagpipe)

class VisualMusicPresenterTest : public QObject
{
    Q_OBJECT

public:
    VisualMusicPresenterTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testSetGetPageView();
    void testSetGetModel();
    void testScoreInserted();

private:
    PageViewDummy *m_pageView;
    VisualMusicPresenter *m_musicPresenter;
    MusicModel *m_musicModel;
};

VisualMusicPresenterTest::VisualMusicPresenterTest()
{
}

void VisualMusicPresenterTest::init()
{
    m_pageView = new PageViewDummy();
    m_musicModel = new MusicModel(this);

    m_musicPresenter = new VisualMusicPresenter(this);
    m_musicPresenter->setPageView(m_pageView);
    m_musicPresenter->setModel(m_musicModel);
}

void VisualMusicPresenterTest::cleanup()
{
    delete m_musicPresenter;
    delete m_pageView;
    delete m_musicModel;
}

void VisualMusicPresenterTest::testSetGetPageView()
{
    QScopedPointer<PageViewInterface> pageView(new PageViewDummy());
    m_musicPresenter->setPageView(pageView.data());
    QVERIFY2(m_musicPresenter->pageView() == pageView.data(), "Wrong page view returned by presenter");
}

void VisualMusicPresenterTest::testSetGetModel()
{
    QStandardItemModel *model = new QStandardItemModel(this);
    m_musicPresenter->setModel(model);
    QVERIFY2(m_musicPresenter->visualMusicModel()->model() == model,
             "Visual music presenter hasn't set abstract item model to visual music model");
    delete model;
}

void VisualMusicPresenterTest::testScoreInserted()
{
    m_musicModel->insertScore(0, "Testscore");

    QVERIFY2(m_musicPresenter->m_interactingScores.count() == 1,
             "No graphical score was inserted");

    InteractingScore *score1 = m_musicPresenter->m_interactingScores.at(0);

    m_musicModel->insertScore(0, "Testscore 2");

    QVERIFY2(m_musicPresenter->m_interactingScores.count() == 2,
             "No second graphical score was inserted");

    InteractingScore *score2 = m_musicPresenter->m_interactingScores.at(0);

    QVERIFY2(score1 != score2,
             "Interacting score inserted in the wrong place");
}

QTEST_MAIN(VisualMusicPresenterTest)

#include "tst_visualmusicpresentertest.moc"
