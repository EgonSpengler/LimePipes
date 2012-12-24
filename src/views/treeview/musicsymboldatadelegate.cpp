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
#include <musicmodelinterface.h>
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
    const MusicModelInterface *model = musicModelFromIndex(index);

    if (isSymbolIndexOk(index) == false)
        return;

    if (model->isIndexSymbol(index) &&
            hasSymbolDelegateData(index) == false)
        return;

    QStringList items = comboBoxItems(index);
    if (!items.empty()) {
        comboBox->insertItems(0, items);

        int currentItemIndex = comboBox->findText(currentSelectedData(index));
        comboBox->setCurrentIndex(currentItemIndex);
    }
}

void MusicSymbolDataDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);

    const MusicModelInterface *musicModel = musicModelFromIndex(index);
    if (!musicModel ||
            !isSymbolIndexOk(index))
        return;

    if (musicModel->isIndexSymbol(index)) {
        setSymbolDataFromSelectedText(model, index, comboBox->currentText());
    }
}

void MusicSymbolDataDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

bool MusicSymbolDataDelegate::isSymbolIndexOk(const QModelIndex &index) const
{
    const MusicModelInterface *model = musicModelFromIndex(index);
    if (model &&
            model->isIndexSymbol(index) &&
            model->isIndexTune(index.parent()))
        return true;
    return false;
}

const MusicModelInterface *MusicSymbolDataDelegate::musicModelFromIndex(const QModelIndex &index) const
{
    const QAbstractItemModel *model = index.model();
    return dynamic_cast<const MusicModelInterface*>(model);
}
