/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALMUSICMODELDUMMY_H
#define VISUALMUSICMODELDUMMY_H

#include <views/graphicsitemview/visualmusicmodel/visualmusicmodelinterface.h>
#include <QObject>

class VisualMusicModelDummy : public QObject,
                              public VisualMusicModelInterface
{
    Q_OBJECT

public:
    VisualMusicModelDummy(QObject *parent=0)
        : QObject(parent) {}
    virtual ~VisualMusicModelDummy() {}

    QGraphicsScene *scene() { return 0; }
    void setModel(QAbstractItemModel *model) { Q_UNUSED(model); }
    QAbstractItemModel *model() const { return 0; }
};

#endif // VISUALMUSICMODELDUMMY_H
