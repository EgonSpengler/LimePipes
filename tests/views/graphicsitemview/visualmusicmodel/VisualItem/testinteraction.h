/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TESTINTERACTION_H
#define TESTINTERACTION_H

#include <views/graphicsitemview/visualmusicmodel/iteminteraction.h>

class TestInteraction : public ItemInteraction
{
    Q_OBJECT
public:
    explicit TestInteraction(QObject *parent = 0);

    void emitDataChanged(const QVariant &data, int dataRole);
};

#endif // TESTINTERACTION_H
