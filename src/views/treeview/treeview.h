/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>

#include <common/pluginmanagerinterface.h>

class PitchDelegate;
class LengthDelegate;

class TreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit TreeView(QWidget *parent = 0);
    ~TreeView();

    void keyPressEvent(QKeyEvent *event);

    PluginManager pluginManager() const;
    void setPluginManager(const PluginManager &pluginManager);

private:
    void handleAddDots();
    void handleDeleteCurrentItem();
    PitchDelegate *m_pitchDelegate;
    LengthDelegate *m_lengthDelegate;
    PluginManager m_pluginManager;
};

#endif // TREEVIEW_H
