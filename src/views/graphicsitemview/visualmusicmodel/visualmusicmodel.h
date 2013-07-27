/**
 * @author Thomas Baumann <teebaum@ymail.com>
 * 
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 * 
 */
#ifndef VISUALMUSICMODEL_H_7R3SY07L
#define VISUALMUSICMODEL_H_7R3SY07L

#include <QObject>
#include "visualmusicmodelinterface.h"

class GraphicsScene;

class VisualMusicModel : public QObject,
                         public VisualMusicModelInterface
{
public:
    explicit VisualMusicModel(QObject *parent=0);
    virtual ~VisualMusicModel();

    QGraphicsScene *scene();
    void setModel(QAbstractItemModel *model);
    QAbstractItemModel *model() const;
    void insertScore(int row, const QString &title);
    void insertTuneIntoScore(int row, const QModelIndex &score, const QString &instrumentName);
    void insertPartIntoTune(int row, const QModelIndex &tune, int measures, bool withRepeat=false);
    void insertMeasureIntoPart(int row, const QModelIndex &part);
    void insertSymbolIntoMeasure(int row, const QModelIndex &measure, const QString &symbolName);
    void dataChanged(const QModelIndex& index);
    void rowsAboutToBeRemoved(const QModelIndex& parent, int start, int end);

private:
    QAbstractItemModel *m_model;
    GraphicsScene *m_scene;
};

#endif // VISUALMUSICMODEL_H_7R3SY07L 
