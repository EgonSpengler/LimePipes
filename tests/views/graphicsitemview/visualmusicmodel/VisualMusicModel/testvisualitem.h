/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TESTVISUALITEM_H
#define TESTVISUALITEM_H

#include <QHash>
#include <views/graphicsitemview/visualmusicmodel/visualitem.h>

class TestVisualItem : public VisualItem
{
    Q_OBJECT
public:
    TestVisualItem(QObject *parent = 0);

    void emitDataChanged(const QVariant& data, int dataRole);
    void emitRowSequenceChanged();

    void insertChildItem(int index, VisualItem *childItem);

    void setData(const QVariant& value, int key);
    bool hasData(int key);
    QVariant data(int key);

    bool insertChildItemCalled() const { return m_insertChildItemCalled; }
    VisualItem *childItemToInsert() const { return m_childItemToInsert; }
    int rowOfChildToInsert() const { return m_rowOfChildToInsert; }

private:
    bool m_insertChildItemCalled;
    VisualItem *m_childItemToInsert;
    int m_rowOfChildToInsert;
    QHash<int, QVariant> m_data;
};

#endif // TESTVISUALITEM_H
