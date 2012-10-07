/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class MusicSymbolDataDelegate
  *
  * A Delegate baseclass for symbol data delegates in a MusicModel.
  */

#include "musicsymboldatadelegate.h"
#include <QComboBox>

QWidget *MusicSymbolDataDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    QComboBox *comboBox = new QComboBox(parent);
    return comboBox;
}

void MusicSymbolDataDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    const MusicModel *model = musicModelFromIndex(index);

    if (isSymbolIndexOk(index) == false)
        return;

    Symbol *symbol = model->symbolFromIndex(index);
    if (symbol &&
        hasSymbolDelegateData(symbol) == false)
        return;

    QStringList items = comboBoxItems(symbol);
    if (!items.empty()) {
        comboBox->insertItems(0, items);

        int currentItemIndex = comboBox->findText(currentSelectedData(symbol));
        comboBox->setCurrentIndex(currentItemIndex);
    }
}

void MusicSymbolDataDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    Q_UNUSED(model)
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    const MusicModel *musicModel = musicModelFromIndex(index);
    if (!musicModel ||
        !isSymbolIndexOk(index))
        return;

    Symbol *symbol = musicModel->symbolFromIndex(index);
    if (symbol) {
        setSymbolDataFromSelectedText(symbol, comboBox->currentText());
    }
}

void MusicSymbolDataDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

bool MusicSymbolDataDelegate::isSymbolIndexOk(const QModelIndex &index) const
{
    const MusicModel *model = musicModelFromIndex(index);
    if (model &&
        model->isIndexSymbol(index) &&
        model->isIndexTune(index.parent()))
        return true;
    return false;
}

const MusicModel *MusicSymbolDataDelegate::musicModelFromIndex(const QModelIndex &index) const
{
    return static_cast<const MusicModel*>(index.model());
}


