/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef LENGTHDELEGATETEST_H
#define LENGTHDELEGATETEST_H

#include <QComboBox>
#include <musicmodel.h>
#include <views/treeview/lengthdelegate.h>

class LengthDelegateTest : public QObject
{
    Q_OBJECT
    
public:
    LengthDelegateTest()
        : m_model(0),
          m_delegate(0),
          m_tuneIndex(0),
          m_symbolWithLengthIndex(0),
          m_symbolWithNoLengthIndex(0),
          m_parentWidget(0),
          m_editor(0) {}
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void testCreateEditor();
    void testSetEditorData();
    void testSetModelData();

private:
    QModelIndex symbolIndex(LP::SymbolDataRole role, bool hasData);
    MusicModel *m_model;
    LengthDelegate *m_delegate;
    QPersistentModelIndex *m_tuneIndex;
    QPersistentModelIndex *m_symbolWithLengthIndex;
    QPersistentModelIndex *m_symbolWithNoLengthIndex;
    QWidget *m_parentWidget;
    QComboBox *m_editor;
    QModelIndex m_lengthIndex;
    QStringList m_instrumentNames;
    QStringList m_symbolNames;
};

#endif
