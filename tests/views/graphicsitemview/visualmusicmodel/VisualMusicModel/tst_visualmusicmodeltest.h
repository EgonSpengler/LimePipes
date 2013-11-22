/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QObject>

class MusicModel;
class VisualMusicModel;

class VisualMusicModelTest : public QObject {
    Q_OBJECT
public:
    explicit VisualMusicModelTest (QObject *parent=0);

private Q_SLOTS:
    void init();
    void cleanup();
    void testSetGetModel();
    void testInsertScore();
    void testInsertTune();
    void testInsertPart();
    void testInsertMeasure();
    void testInsertSymbol();
    void testVisualItemFromIndex();
    void testScoreDataChanged();

private:
    MusicModel *m_musicModel;
    VisualMusicModel *m_visualMusicModel;
};
