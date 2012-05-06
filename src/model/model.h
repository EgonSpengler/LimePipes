/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MODEL_H
#define MODEL_H

#include <QStandardItemModel>

class Model : public QStandardItemModel
{
    Q_OBJECT
public:

    /*! The Itemtypes used by this Model */
    enum ItemTypes {
        SheetMusicType = QStandardItem::UserType +1,
        TuneType = QStandardItem::UserType + 2,
        PartType = QStandardItem::UserType + 3,
        BarType = QStandardItem::UserType + 4,
        SymbolType = QStandardItem::UserType + 5
    };

    explicit Model(QObject *parent = 0);

signals:

public slots:

};

#endif // MODEL_H
