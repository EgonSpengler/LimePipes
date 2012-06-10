#ifndef MODEL_ITEMTYPES_H
#define MODEL_ITEMTYPES_H

#include <QStandardItemModel>

/*! The Itemtypes used by this Model */
const int ScoreType = QStandardItem::UserType +1;
const int TuneType = QStandardItem::UserType + 2;
const int PartType = QStandardItem::UserType + 3;
const int BarType = QStandardItem::UserType + 4;
const int SymbolType = QStandardItem::UserType + 5;
const int MelodyNoteType = QStandardItem::UserType + 6;

#endif // MODEL_ITEMTYPES_H
