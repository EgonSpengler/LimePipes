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
#include <common/pluginmanagerinterface.h>

class MusicModelInterface;

class MusicSymbolDataDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit MusicSymbolDataDelegate(QObject *parent = 0) : QItemDelegate(parent) {}
    virtual ~MusicSymbolDataDelegate() {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    virtual QStringList comboBoxItems(const QModelIndex &symbolIndex) const = 0;
    virtual QString currentSelectedData(const QModelIndex &symbolIndex) const = 0;
    virtual bool hasSymbolDelegateData(const QModelIndex &symbolIndex) const = 0;
    virtual void setSymbolDataFromSelectedText(QAbstractItemModel *model, const QModelIndex &symbolIndex, const QString &text) const = 0;

    PluginManager pluginManager() const;
    void setPluginManager(const PluginManager &pluginManager);

private:
    const MusicModelInterface *musicModelFromIndex(const QModelIndex &index) const;
    bool isSymbolIndexOk(const QModelIndex &index) const;
    PluginManager m_pluginManager;
};

#endif // MUSICSYMBOLDATADELEGATE_H
