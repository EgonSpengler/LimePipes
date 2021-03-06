/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "treeview.h"
#include <QKeyEvent>
#include "pitchdelegate.h"
#include "lengthdelegate.h"
#include <common/itemdataroles.h>
#include <plugins/IntegratedSymbols/integratedsymbolsdefines.h>

TreeView::TreeView(QWidget *parent)
    : QTreeView(parent)
{
    m_pitchDelegate = new PitchDelegate();
    setItemDelegateForColumn(1, m_pitchDelegate);

    m_lengthDelegate = new LengthDelegate();
    setItemDelegateForColumn(2, m_lengthDelegate);

    setSelectionMode(QAbstractItemView::SingleSelection);
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
}

TreeView::~TreeView()
{
    delete m_pitchDelegate;
    delete m_lengthDelegate;
}

void TreeView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Period:
        handleAddDots();
        break;
    case Qt::Key_Delete:
        handleDeleteCurrentItem();
        break;
    default:
        QTreeView::keyPressEvent(event);
    }
}

void TreeView::handleAddDots()
{
    // Add dots to possible melody note under current index
    QModelIndex index = currentIndex();
    QVariant dotsVariant = index.data(LP::MelodyNoteDots);
    if (!dotsVariant.isValid())
        return;

    if (dotsVariant.canConvert<int>()) {
        int dots = dotsVariant.value<int>();

        dots++;

        if (dots > MelodyNoteMaxDots)
            dots = 0;

        model()->setData(index, QVariant(dots), LP::MelodyNoteDots);
        update(index);
    }
}

void TreeView::handleDeleteCurrentItem()
{
    QModelIndex index = currentIndex();
    model()->removeRow(index.row(), index.parent());
}

PluginManager TreeView::pluginManager() const
{
    return m_pluginManager;
}

void TreeView::setPluginManager(const PluginManager &pluginManager)
{
    m_pluginManager = pluginManager;
    m_pitchDelegate->setPluginManager(pluginManager);
    m_lengthDelegate->setPluginManager(pluginManager);
}

