/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */
#ifndef VISUALMUSICMODELINTERFACE_H_MRBWTAGO
#define VISUALMUSICMODELINTERFACE_H_MRBWTAGO

#include <QGraphicsScene>
#include <QAbstractItemModel>

class VisualMusicModelInterface {
public:
    virtual ~VisualMusicModelInterface() {}
    virtual QGraphicsScene *scene() = 0;
    virtual void setModel(QAbstractItemModel *model) = 0;
    virtual QAbstractItemModel *model() const = 0;
};


#endif // VISUALMUSICMODELINTERFACE_H_MRBWTAGO
