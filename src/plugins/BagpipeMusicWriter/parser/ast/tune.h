/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TUNE_H
#define TUNE_H

#include <QString>

#include "musicitem.h"

class Tune : public MusicItem
{
public:
    explicit Tune(MusicItem *parent=0);

    void accept(AstVisitorInterface *visitor);

    QString title;
    QString composer;
    QString arranger;
};

#endif // TUNE_H
