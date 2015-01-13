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
#include <QList>
#include <QString>

#include "parser/ast/AstDefines.h"
#include "parser/ast/AstVisitorInterface.h"

class MelodyNote;
class TimeSignature;
class Embellishment;
class EmbellishmentRules;

/*!
 * \brief The GuidoCodeVisitor class
 * Generates Guido code from an abstract syntax tree.
 */
class GuidoCodeVisitor : public AstVisitorInterface
{
public:
    explicit GuidoCodeVisitor();
    ~GuidoCodeVisitor();

    void visit(Score *score);
    void visit(Tune *tune);
    void visit(Part *part);
    void visit(Symbol *symbol);
    void visit(SymbolGroup *symbolGroup);

    void finishVisit(Score *score);
    void finishVisit(Tune *tune);
    void finishVisit(Part *part);
    void finishVisit(Symbol *symbol);
    void finishVisit(SymbolGroup *symbolGroup);

    QString guidoCode() const;

    void setEmbellishmentRules(EmbellishmentRules *embellishmentRules);

private:
    static QHash<SymbolPitch, QString> s_melodyNotePitchMap;
    static QHash<SymbolPitch, QString> initMelodyNotePitchMap();

    void addMelodyNote(MelodyNote *note);
    void addTimeSignature(TimeSignature *time);
    void addEmbellishment(const Embellishment &embellishment);
    void addGraceSequence(const QList<SymbolPitch> &pitches);
    void visitSingleSymbol(const Symbol *symbol);
    void visitSymbolGroup(const SymbolGroup *symbolGroup);

    QStringList m_guidoCode;
    EmbellishmentRules *m_embellishmentRules;
};

#endif // GUIDOCODEVISITOR_H
