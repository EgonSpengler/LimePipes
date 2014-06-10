/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class MelodyNote
  * A @ref Symbol "melody note symbol".
  */

#include "melodynote.h"
#include <common/defines.h>
#include <QXmlStreamWriter>
#include "../integratedsymbolsdefines.h"

MelodyNote::MelodyNote()
    : Symbol(LP::MelodyNote, tr("Melody Note"))
{
    initSymbol();
}

MelodyNote::MelodyNote(int type, const QString &name)
    : Symbol(type, name)
{
    initSymbol();
}

bool MelodyNote::itemSupportsWritingOfData(int role) const
{
    if (role == LP::MelodyNoteDots)
        return true;
    return Symbol::itemSupportsWritingOfData(role);
}

void MelodyNote::beforeWritingData(QVariant &value, int role)
{
    if (!value.isValid())
        return;

    if (role == LP::MelodyNoteDots &&
            value.canConvert<int>()) {
        if (value.value<int>() < 0)
            value.setValue(0);
        if (value.value<int>() > MelodyNoteMaxDots)
            value.setValue(MelodyNoteMaxDots);
    }
}

void MelodyNote::initSymbol()
{
    initData(0, LP::MelodyNoteDots);
    initData(QVariant::fromValue<SymbolCategory>(SymbolCategory::Graphical), LP::SymbolCategory);
    setSymbolOptions(Symbol::HasPitch |
                     Symbol::HasLength);
}

void MelodyNote::writeItemDataToXmlStream(QXmlStreamWriter *writer)
{
    Symbol::writeItemDataToXmlStream(writer);

    QVariant dotsVar = data(LP::MelodyNoteDots);
    if (dotsVar.isValid() &&
            dotsVar.canConvert<int>()) {
        int dots = dotsVar.value<int>();
        if (dots > 0)
            writer->writeTextElement("DOTS", QString::number(dots, 10));
    }
}

void MelodyNote::readCurrentElementFromXmlStream(QXmlStreamReader *reader)
{
    if (QString("DOTS").compare(reader->name(), Qt::CaseInsensitive) == 0) {
        int dots = reader->readElementText().toInt();
        setData(dots, LP::MelodyNoteDots);
    }
    Symbol::readCurrentElementFromXmlStream(reader);
}
