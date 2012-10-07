/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICSYMBOLDATADELEGATE_H
#define MUSICSYMBOLDATADELEGATE_H

#include <QItemDelegate>
#include <musicmodel.h>

class MusicSymbolDataDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit MusicSymbolDataDelegate(QObject *parent = 0)
        : QItemDelegate(parent) {}
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    virtual QStringList comboBoxItems(const Symbol *symbol) const = 0;
    virtual bool hasSymbolDelegateData(const Symbol *symbol) const = 0;
    virtual QString currentSelectedData(const Symbol *symbol) const = 0;
    virtual void setSymbolDataFromSelectedText(Symbol *symbol, const QString &text) const = 0;

private:
    const MusicModel *musicModelFromIndex(const QModelIndex &index) const;
    bool isSymbolIndexOk(const QModelIndex &index) const;
};

#endif // MUSICSYMBOLDATADELEGATE_H
