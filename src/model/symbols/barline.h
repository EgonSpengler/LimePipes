/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef BARLINE_H
#define BARLINE_H

#include <QCoreApplication>
#include <QMetaType>
#include <symbol.h>

class BarLine : public Symbol
{
    Q_DECLARE_TR_FUNCTIONS(Bar)
public:
    enum Type {
        StartPart,
        EndPart,
        Normal
    };
    const static QString SymbolName;

    explicit BarLine(Type type=Normal, MusicItem *parent=0);

    bool itemSupportsWritingOfData(int role) const;
    void beforeWritingData(QVariant &value, int role);

    void writeItemDataToXmlStream(QXmlStreamWriter *writer);
    void readCurrentElementFromXmlStream(QXmlStreamReader *reader);

private:
    QString typeName(Type barType);
    BarLine::Type typeForName(const QString &typeName);
};

Q_DECLARE_METATYPE(BarLine::Type)

#endif // BARLINE_H
