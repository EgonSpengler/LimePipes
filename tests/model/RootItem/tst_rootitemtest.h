#ifndef __ROOTITEM_TEST__
#define __ROOTITEM_TEST__

#include <QObject>
#include <src/model/rootitem.h>

class RootItemTest : public QObject
{
    Q_OBJECT

public:
    RootItemTest()
        : m_rootItem(0) {}

private Q_SLOTS:
    void init();
    void cleanup();
    void testType();
    void testChildType();

private:
    RootItem *m_rootItem;
};

#endif
