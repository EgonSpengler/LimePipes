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

signals:
    void insertScoreCalled();
    void insertTuneIntoScoreCalled();
    void insertPartIntoTuneCalled();
    void insertMeasureIntoPartCalled();
    void insertSymbolIntoMeasureCalled();

public:
    VisualMusicModelDummy(QObject *parent=0)
        : QObject(parent) {}
    virtual ~VisualMusicModelDummy() {}

    QGraphicsScene *scene() { return 0; }

    void setModel(QAbstractItemModel *model) { Q_UNUSED(model); }

    QAbstractItemModel *model() const { return 0; }

    void insertScore(int row, const QString &title)
    {
        emit insertScoreCalled();
    }

    void insertTuneIntoScore(int row, const QModelIndex &score)
    {
        emit insertTuneIntoScoreCalled();
    }

    void insertPartIntoTune(int row, const QModelIndex &tune)
    {
        emit insertPartIntoTuneCalled();
    }

    void insertMeasureIntoPart(int row, const QModelIndex &part)
    {
        emit insertMeasureIntoPartCalled();
    }

    void insertSymbolIntoMeasure(int row, const QModelIndex &measure)
    {
        emit insertSymbolIntoMeasureCalled();
    }

    void dataChanged(const QModelIndex &index)
    {
    }

    void rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end)
    {
    }
};

#endif // VISUALMUSICMODELDUMMY_H
