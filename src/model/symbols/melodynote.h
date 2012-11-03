/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MELODYNOTE_H
#define MELODYNOTE_H

#include <QCoreApplication>
#include <symbol.h>
#include <melodynotegraphicbuilder.h>

class MelodyNote : public Symbol
{
    Q_DECLARE_TR_FUNCTIONS(MelodyNote)
public:
    explicit MelodyNote();
    explicit MelodyNote(int type, const QString &name);

    bool itemSupportsWritingOfData(int role) const;
    void beforeWritingData(QVariant &value, int role);
    const static int MaxDots = 4;

    void writeItemDataToXmlStream(QXmlStreamWriter *writer);

private:
    void initSymbol();
};

#endif // MELODYNOTE_H
