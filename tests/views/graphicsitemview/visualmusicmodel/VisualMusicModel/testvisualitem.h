/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TESTVISUALITEM_H
#define TESTVISUALITEM_H

#include <views/graphicsitemview/visualmusicmodel/visualitem.h>

class TestVisualItem : public VisualItem
{
    Q_OBJECT
public:
    TestVisualItem(QObject *parent = 0);

    void emitDataChanged(const QVariant& data, int dataRole);
    void emitRowSequenceChanged();
};

#endif // TESTVISUALITEM_H
