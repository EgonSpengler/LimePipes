/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PITCHDELEGATE_H
#define PITCHDELEGATE_H

#include <QItemDelegate>
#include <symbol.h>
#include <musicmodel.h>

class PitchDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit PitchDelegate(QObject *parent = 0);
    
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem & option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    bool isSymbolIndexOk(const QModelIndex &index) const;
    const MusicModel *musicModelFromIndex(const QModelIndex &index) const;
};

#endif // PITCHDELEGATE_H
