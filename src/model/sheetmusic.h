/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SHEETMUSIC_H
#define SHEETMUSIC_H

#include <QStandardItem>
#include "model.h"

class SheetMusic : public QStandardItem
{
public:
    explicit SheetMusic();
    int type() const { return Model::SheetMusicType; }

signals:

public slots:

};

#endif // SHEETMUSIC_H
