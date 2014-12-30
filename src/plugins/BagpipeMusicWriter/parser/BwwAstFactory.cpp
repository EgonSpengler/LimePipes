/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QDir>
#include <QDebug>

#include "ast/score.h"
#include "ast/tune.h"
#include "ast/part.h"
#include "ast/symbol.h"
#include "ast/melodynote.h"
#include "ast/timesignature.h"
#include "ast/embellishment.h"

#include "GuidoCodeVisitor.h"
#include "EmbellishmentRules.h"
#include "EmbellishmentContextVisitor.h"
#include "BwwAstFactory.h"

BwwAstFactory::BwwAstFactory()
    : m_score(0),
      m_currentTune(0),
      m_currentPart(0),
      m_currentSymbol(0)
{
    initAst();

    m_embellishmentRules = new EmbellishmentRules;
    m_embellishmentRules->addRulesFromDirectory(QDir(":/embellishment_resources"));
}

BwwAstFactory::~BwwAstFactory()
{
    delete m_score;
    m_embellishmentRules->deleteLater();
}

void BwwAstFactory::initAst()
{
    m_score = new Score;
    m_currentTune = new Tune(m_score);
    m_currentPart = new Part(m_currentTune);
}

void BwwAstFactory::clear()
{
    qDebug() << "Clear bww guido factory";

    delete m_score;
    initAst();
}

void BwwAstFactory::setTitle(const QString &title)
{
    m_currentTune->title = title;
}

void BwwAstFactory::addMelodyNote(const QString &bwwCode)
{
    MelodyNote *melodyNote = new MelodyNote(bwwCode);
    m_currentPart->addChild(melodyNote);
    m_currentSymbol = melodyNote;
}

void BwwAstFactory::addBarline()
{
    Symbol *bar = new Symbol(T_Bar);
    m_currentPart->addChild(bar);
    m_currentSymbol = bar;
}

void BwwAstFactory::endPart(bool repeat)
{
    m_currentPart->setRepeat(repeat);
    m_currentPart = new Part(m_currentTune);
}

void BwwAstFactory::addTimeSignature(const QString &bwwCode)
{
    TimeSignature *timeSig = new TimeSignature(bwwCode);
    m_currentPart->addChild(timeSig);
    m_currentSymbol = timeSig;
}

void BwwAstFactory::addMelodyNoteDots(int dots)
{
    if (dots <= 0 ||
            dots >3) {
        qWarning() << "Only dots between 1 and 3 are allowed to add";
        return;
    }

    if (!m_currentSymbol) {
        qWarning() << "Dots can't be added, if no symbol has been added before";
        return;
    }

    if (m_currentSymbol->type() != T_Melody) {
        qWarning() << "Current symbol is no melody note. Can't add dots.";
        return;
    }

    MelodyNote *melodyNote = static_cast<MelodyNote*>(m_currentSymbol);
    if (melodyNote) {
        melodyNote->setDots(dots);
    }
}

void BwwAstFactory::addSingleGrace(const QString &bwwCode)
{
    if (!bwwCode.count()) {
        return;
    }

    const QChar gracePitch(bwwCode.at(0));
    SymbolPitch pitch = NoPitch;
    if (gracePitch == QLatin1Char('a')) { pitch = LowA; }
    if (gracePitch == QLatin1Char('b')) { pitch = B; }
    if (gracePitch == QLatin1Char('c')) { pitch = C; }
    if (gracePitch == QLatin1Char('d')) { pitch = D; }
    if (gracePitch == QLatin1Char('e')) { pitch = E; }
    if (gracePitch == QLatin1Char('f')) { pitch = F; }
    if (gracePitch == QLatin1Char('g')) { pitch = HighG; }
    if (gracePitch == QLatin1Char('t')) { pitch = HighA; }

    Embellishment *embellishment = new Embellishment(Embellishment::SINGLE_GRACE, pitch);
    m_currentPart->addChild(embellishment);
    m_currentSymbol = embellishment;
}

void BwwAstFactory::addDoubling(const QString &bwwCode, Embellishment::Type type)
{
    QString code(bwwCode);
    switch (type) {
    case Embellishment::DOUBLING_REG:
        code.remove(0, 2);
        break;
    case Embellishment::DOUBLING_HALF:
    case Embellishment::DOUBLING_THUMB:
        code.remove(0, 3);
        break;
    default:
        qWarning() << "No doubling to add" << bwwCode;
        return;
    }

    SymbolPitch pitch = pitchFromString(code);
    if (pitch == NoPitch) {
        qWarning() << code << " is no pitch for embellishment";
        return;
    }

    Embellishment *embellishment = new Embellishment(type, pitch);
    m_currentPart->addChild(embellishment);
    m_currentSymbol = embellishment;
}

void BwwAstFactory::addGrip(const QString &bwwCode, Embellishment::Type type)
{
    QString code(bwwCode);
    Embellishment *embellishment = Q_NULLPTR;

    switch (type) {
    case Embellishment::GRIP_REG:
    case Embellishment::GRIP_HALF:
    case Embellishment::GRIP_B:
        // These grips have no context
        embellishment = new Embellishment(type);
        break;
    case Embellishment::GRIP_THUMB:
    case Embellishment::GRIP_G:
    case Embellishment::GRIP_LONG:
    {
        code.remove(0, 4);
        SymbolPitch pitch = pitchFromString(code);
        if (pitch == NoPitch) {
            qWarning() << code << " is no pitch for grip embellishment";
            return;
        }

        embellishment = new Embellishment(type, pitch);
        break;
    }
    default:
        qWarning() << "No grip to add: " << bwwCode;
        return;
    }

    if (!embellishment) {
        qWarning() << "No embellishment added for grip code: " << bwwCode;
        return;
    }

    m_currentPart->addChild(embellishment);
    m_currentSymbol = embellishment;
}

SymbolPitch BwwAstFactory::pitchFromString(const QString &pitchString)
{
    SymbolPitch pitch = NoPitch;
    if (pitchString == QStringLiteral("lg")) { pitch = LowG; }
    if (pitchString == QStringLiteral("la")) { pitch = LowA; }
    if (pitchString == QStringLiteral("b")) { pitch = B; }
    if (pitchString == QStringLiteral("c")) { pitch = C; }
    if (pitchString == QStringLiteral("d")) { pitch = D; }
    if (pitchString == QStringLiteral("e")) { pitch = E; }
    if (pitchString == QStringLiteral("f")) { pitch = F; }
    if (pitchString == QStringLiteral("hg")) { pitch = HighG; }
    if (pitchString == QStringLiteral("ha")) { pitch = HighA; }
    return pitch;
}

QString BwwAstFactory::getGuidoCode()
{
    EmbellishmentContextVisitor contextVisitor;
    m_score->accept(&contextVisitor);

    GuidoCodeVisitor codeVisitor;
    codeVisitor.setEmbellishmentRules(m_embellishmentRules);
    m_score->accept(&codeVisitor);

    return codeVisitor.guidoCode();
}
