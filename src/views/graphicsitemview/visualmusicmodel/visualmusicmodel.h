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
#include "abstractvisualitem.h"
#include "../visualmusicmodelinterface.h"

class GraphicsScene;
class VisualRootItem;
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
    AbstractScorePropertiesHolder *scorePropertiesHolderFromIndex(const QModelIndex& scoreIndex);
    VisualScoreInterface *visualScoreFromIndex(const QModelIndex& scoreIndex);

signals:
    void scoreInserted(const QModelIndex& scoreIndex);
    void tuneInserted(const QModelIndex& tuneIndex);
    void partInserted(const QModelIndex& partIndex);
    void measureInserted(const QModelIndex& measureIndex);
    void symbolInserted(const QModelIndex& symbolIndex);

private slots:
    void rowsInserted(const QModelIndex &parent, int start, int end);

private:
    void createRootItemIfNotPresent();
    void insertNewScores(const QModelIndex& index, int start, int end);
    void insertNewTunes(const QModelIndex& index, int start, int end);
    void insertNewParts(const QModelIndex& index, int start, int end);
    void insertNewMeasures(const QModelIndex& index, int start, int end);
    void insertNewSymbols(const QModelIndex& index, int start, int end);
    QAbstractItemModel *m_model;
    VisualRootItem *m_rootItem;
    QHash<QPersistentModelIndex, VisualScore*> m_visualScoreIndexes;
    QHash<QPersistentModelIndex, VisualTune*> m_visualTuneIndexes;
    QHash<QPersistentModelIndex, VisualPart*> m_visualPartIndexes;
    QHash<QPersistentModelIndex, VisualMeasure*> m_visualMeasureIndexes;
    QHash<QPersistentModelIndex, VisualSymbol*> m_visualSymbolIndexes;
};

#endif // VISUALMUSICMODEL_H_7R3SY07L
