/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PITCHDELEGATETEST_H
#define PITCHDELEGATETEST_H

#include <QComboBox>
#include <musicmodel.h>
#include <views/treeview/pitchdelegate.h>

class PitchDelegateTest : public QObject
{
    Q_OBJECT
    
public:
    PitchDelegateTest()
        : m_model(0),
          m_delegate(0),
          m_instrument(0),
          m_tuneIndex(0),
          m_symbolWithPitchIndex(0),
          m_symbolWithNoPitchIndex(0),
          m_parentWidget(0),
          m_editor(0) {}
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void testCreateEditor();
    void testSetEditorData();
    void setModelData();

private:
    QModelIndex symbolIndex(LP::DataRole role, bool hasData);
    MusicModel *m_model;
    PitchDelegate *m_delegate;
    InstrumentPtr m_instrument;
    QPersistentModelIndex *m_tuneIndex;
    QPersistentModelIndex *m_symbolWithPitchIndex;
    QPersistentModelIndex *m_symbolWithNoPitchIndex;
    QWidget *m_parentWidget;
    QComboBox *m_editor;
    QModelIndex m_pitchIndex;
    QStringList m_instrumentNames;
    QStringList m_symbolNames;
};

#endif
