/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TST_GRAPHICSITEMVIEWTEST_H
#define TST_GRAPHICSITEMVIEWTEST_H

#include <QObject>

class GraphicsItemView;
class VisualMusicModelDummy;
class MusicModel;

class GraphicsItemViewTest : public QObject
{
    Q_OBJECT
public:
    GraphicsItemViewTest();

private Q_SLOTS:
    void init();
    void cleanup();

private:
    GraphicsItemView *m_graphicsItemView;
    MusicModel *m_model;
};

#endif // TST_GRAPHICSITEMVIEWTEST_H
