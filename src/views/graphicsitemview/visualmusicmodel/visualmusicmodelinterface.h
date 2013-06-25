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
    explicit VisualMusicModelInterface ();
    virtual ~VisualMusicModelInterface ();

    QGraphicsScene *scene() = 0;
    void setModel(QAbstractItemModel *model) = 0;
    virtual insertScore(int row, const QString &title) = 0;
    virtual insertTuneIntoScore(int row, const QModelIndex &score, const QString &instrumentName) = 0;
    virtual insertPartIntoTune(int row, const QModelIndex &tune, int measures, bool withRepeat=false) = 0;
    virtual insertMeasureIntoPart(int row, const QModelIndex &part) = 0;
    virtual insertSymbolIntoMeasure(int row, const QModelIndex &measure, const QString &symbolName) = 0;
    virtual dataChanged(const QModelIndex& index) = 0;
    virtual rowsAboutToBeRemoved(const QModelIndex& parent, int start, int end) = 0;
};


#endif // VISUALMUSICMODELINTERFACE_H_MRBWTAGO 
