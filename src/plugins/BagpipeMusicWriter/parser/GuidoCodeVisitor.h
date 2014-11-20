/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GUIDOCODEVISITOR_H
#define GUIDOCODEVISITOR_H

#include <QHash>
#include <QString>

#include "parser/ast/AstDefines.h"
#include "parser/ast/AstVisitorInterface.h"

class MelodyNote;
class TimeSignature;

class GuidoCodeVisitor : public AstVisitorInterface
{
public:
    explicit GuidoCodeVisitor();

    void visit(Score *score);
    void visit(Tune *tune);
    void visit(Part *part);
    void visit(Symbol *symbol);

    void finishVisit(Score *score);
    void finishVisit(Tune *tune);
    void finishVisit(Part *part);
    void finishVisit(Symbol *symbol);

    QString guidoCode() const;

private:
    static QHash<SymbolPitch, QString> s_melodyNotePitchMap;
    static QHash<SymbolPitch, QString> initMelodyNotePitchMap();

    void addMelodyNote(MelodyNote *note);
    void addTimeSignature(TimeSignature *time);

    QStringList m_guidoCode;
};

#endif // GUIDOCODEVISITOR_H
