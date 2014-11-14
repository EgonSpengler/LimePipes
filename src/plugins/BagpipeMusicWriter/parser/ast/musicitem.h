/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICITEM_H
#define MUSICITEM_H

#include <QList>

namespace LP {
enum class ItemType {
    NoItemType,
    RootItemType,
    ScoreType,
    TuneType,
    PartType,
    MeasureType,
    SymbolType
};

}

class AstVisitorInterface;

class MusicItem
{
public:
    explicit MusicItem(MusicItem *parent=0);
    virtual ~MusicItem();

    MusicItem *parent() const { return m_parent; }
    void setParent(MusicItem *parent);

    bool hasChildren() const { return !m_children.isEmpty(); }
    bool insertChild(int row, MusicItem *item);
    bool addChild(MusicItem *item);
    void swapChildren(int oldRow, int newRow) { m_children.swap(oldRow, newRow); }
    int rowOfChild(MusicItem *item) const { return m_children.indexOf(item); }
    int childCount() const { return m_children.count(); }
    MusicItem *childAt(int row) const { return m_children.value(row); }
    MusicItem *takeChild(int row);
    QList<MusicItem*> children() const { return m_children; }

    virtual void accept(AstVisitorInterface *visitor) =0;

protected:
    void visitChildren(AstVisitorInterface *visitor);
    MusicItem *m_parent;

private:
    QList<MusicItem*> m_children;
};

#endif // MUSICITEM_H
