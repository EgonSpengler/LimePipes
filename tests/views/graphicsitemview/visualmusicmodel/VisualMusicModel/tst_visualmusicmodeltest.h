/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QObject>
#include <common/pluginmanagerinterface.h>

class MusicModel;
class VisualMusicModel;
class TestVisualItemFactory;

class VisualMusicModelTest : public QObject {
    Q_OBJECT
public:
    explicit VisualMusicModelTest (QObject *parent=0);

private Q_SLOTS:
    void init();
    void cleanup();
    void testSetGetModel();
    void testVisualItemFromIndex();
    void testInsertScore();
    void testScoreDataChanged();
    void testInsertTune();
    void testInsertPart();
    void testInsertMeasure();
    void testInsertSymbol();
    void testInsertChildItemCallOnVisualItem();

private:
    MusicModel *m_musicModel;
    VisualMusicModel *m_visualMusicModel;
    TestVisualItemFactory *m_itemFactory;
    PluginManager m_pluginManager;
};
