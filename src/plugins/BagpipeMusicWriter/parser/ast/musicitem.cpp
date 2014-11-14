/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */


#include <QDebug>

#include "musicitem.h"

using namespace LP;

MusicItem::MusicItem(MusicItem *parent)
    : m_parent(parent)
{
    if (m_parent)
        m_parent->addChild(this);
    else
        m_parent = 0;
}

MusicItem::~MusicItem()
{
    qDeleteAll(m_children);
}

void MusicItem::setParent(MusicItem *parent)
{
    Q_ASSERT(parent);

    if (m_parent != 0) {
        int rowOfThisItemInParent = m_parent->rowOfChild(this);
        Q_ASSERT(rowOfThisItemInParent != -1);
        MusicItem *thisItem = m_parent->takeChild(rowOfThisItemInParent);
        Q_ASSERT(thisItem == this);
        Q_ASSERT(m_parent == 0);
        Q_UNUSED(thisItem)
    }

    m_parent = parent;
}

bool MusicItem::insertChild(int row, MusicItem *item)
{
    item->m_parent = this;
    m_children.insert(row, item);
    return true;
}

bool MusicItem::addChild(MusicItem *item)
{
    if (!item) {
        qWarning() << "Can't add 0 child music item";
        return false;
    }

    item->m_parent = this;
    m_children << item;
    return true;
}

MusicItem *MusicItem::takeChild(int row)
{
    MusicItem *item = m_children.takeAt(row);
    Q_ASSERT(item);
    item->m_parent = 0;
    return item;
}

void MusicItem::visitChildren(AstVisitorInterface *visitor)
{
    foreach (MusicItem *childItem, m_children) {
        childItem->accept(visitor);
    }
}
