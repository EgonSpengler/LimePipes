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
    virtual void insertScore(int row, const QString &title) = 0;
    virtual void insertTuneIntoScore(int row, const QModelIndex &score) = 0;
    virtual void insertPartIntoTune(int row, const QModelIndex &tune) = 0;
    virtual void insertMeasureIntoPart(int row, const QModelIndex &part) = 0;
    virtual void insertSymbolIntoMeasure(int row, const QModelIndex &measure) = 0;
    virtual void dataChanged(const QModelIndex& index) = 0;
    virtual void rowsAboutToBeRemoved(const QModelIndex& parent, int start, int end) = 0;
};


#endif // VISUALMUSICMODELINTERFACE_H_MRBWTAGO
