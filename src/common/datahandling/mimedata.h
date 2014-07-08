/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MIMEDATA_H
#define MIMEDATA_H

#include <QJsonArray>
#include <common/defines.h>

class QMimeData;

class MimeData
{
public:
    MimeData() {}

    static QMimeData *fromJsonArray(const QJsonArray &array);
    static QJsonArray toJsonArray(const QMimeData *mimeData);

    static QString mimeTypeForItemType(LP::ItemType type);
    static QString supportedMimeTypeFromData(const QMimeData *data);
};

#endif // MIMEDATA_H
