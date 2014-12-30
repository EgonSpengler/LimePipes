/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef BWWASTFACTORY_H
#define BWWASTFACTORY_H

#include <QString>
#include <QStringList>
#include <QList>

#include "ast/embellishment.h"

class Score;
class Tune;
class Part;
class Symbol;
class EmbellishmentRules;

class BwwAstFactory
{
public:
    explicit BwwAstFactory();
    ~BwwAstFactory();

    void clear();

    void setTitle(const QString &title);
    void addMelodyNote(const QString &bwwCode);
    void addMelodyNoteDots(int dots);
    void addSingleGrace(const QString &bwwCode);
    void addDoubling(const QString &bwwCode, Embellishment::Type type);
    void addGrip(const QString &bwwCode, Embellishment::Type type);

    void addBarline();
    void endPart(bool repeat);
    void addTimeSignature(const QString &bwwCode);

    QString getGuidoCode();
private:
    void initAst();
    SymbolPitch pitchFromString(const QString &pitchString);

    Score *m_score;
    Tune *m_currentTune;
    Part *m_currentPart;
    Symbol *m_currentSymbol;
    EmbellishmentRules *m_embellishmentRules;
};

#endif // BWWASTFACTORY_H
