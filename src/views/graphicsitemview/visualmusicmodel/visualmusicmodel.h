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
#include <QHash>
#include <QPersistentModelIndex>
#include "visualitem.h"
#include "../visualmusicmodelinterface.h"

class GraphicsScene;
class VisualScore;
class VisualTune;
class VisualPart;
class VisualMeasure;
class VisualSymbol;

class VisualMusicModel : public QObject,
                         public VisualMusicModelInterface
{
    Q_OBJECT

    friend class VisualMusicModelTest;

public:
    explicit VisualMusicModel(QObject *parent=0);
    virtual ~VisualMusicModel();

    // VisualMusicModelInterface
    void setModel(QAbstractItemModel *model);
    QAbstractItemModel *model() const;
    VisualItem *visualItemFromIndex(const QModelIndex& scoreIndex);

signals:
    void scoreRowSequenceChanged(int scoreIndex);

private slots:
    void rowsInserted(const QModelIndex &parent, int start, int end);
    void scoreDataChanged(const QVariant& value, int dataRole);
    void itemRowSequenceChanged();

private:
    void insertNewScores(const QModelIndex& index, int start, int end);
    void insertNewTunes(const QModelIndex& index, int start, int end);
    void insertNewParts(const QModelIndex& index, int start, int end);
    void insertNewMeasures(const QModelIndex& index, int start, int end);
    void insertNewSymbols(const QModelIndex& index, int start, int end);
    void insertVisualItem(QPersistentModelIndex itemIndex, VisualItem *item);
    QAbstractItemModel *m_model;
    QHash<QPersistentModelIndex, VisualItem*> m_visualItemIndexes;
};

#endif // VISUALMUSICMODEL_H_7R3SY07L
