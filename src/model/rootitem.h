/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ROOTITEM_H
#define ROOTITEM_H

#include <musicitem.h>

class RootItem : public MusicItem
{
public:
    explicit RootItem();

    bool itemSupportsWritingOfData(int role) const;
    void writeItemDataToXmlStream(QXmlStreamWriter *writer) { Q_UNUSED(writer) }
};

#endif // ROOTITEM_H
