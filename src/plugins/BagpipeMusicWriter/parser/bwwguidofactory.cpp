/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QDebug>

#include "ast/score.h"
#include "ast/tune.h"
#include "ast/part.h"
#include "ast/symbol.h"
#include "ast/melodynote.h"
#include "ast/timesignature.h"

#include "GuidoCodeVisitor.h"
#include "bwwguidofactory.h"


BwwGuidoFactory::BwwGuidoFactory()
    : m_score(0),
      m_currentTune(0),
      m_currentPart(0),
      m_currentSymbol(0)
{
    initAst();
}

BwwGuidoFactory::~BwwGuidoFactory()
{
    delete m_score;
}

void BwwGuidoFactory::initAst()
{
    m_score = new Score;
    m_currentTune = new Tune(m_score);
    m_currentPart = new Part(m_currentTune);
}

void BwwGuidoFactory::clear()
{
    qDebug() << "Clear bww guido factory";

    delete m_score;
    initAst();
}

void BwwGuidoFactory::setTitle(const QString &title)
{
    m_currentTune->title = title;
}

void BwwGuidoFactory::addMelodyNote(const QString &bwwCode)
{
    MelodyNote *melodyNote = new MelodyNote(bwwCode);
    m_currentPart->addChild(melodyNote);
    m_currentSymbol = melodyNote;
}

void BwwGuidoFactory::addBarline()
{
    Symbol *bar = new Symbol(T_Bar);
    m_currentPart->addChild(bar);
    m_currentSymbol = bar;
}

void BwwGuidoFactory::endPart(bool repeat)
{
    m_currentPart->setRepeat(repeat);
    m_currentPart = new Part(m_currentTune);
}

void BwwGuidoFactory::addTimeSignature(const QString &bwwCode)
{
    TimeSignature *timeSig = new TimeSignature(bwwCode);
    m_currentPart->addChild(timeSig);
    m_currentSymbol = timeSig;
}

void BwwGuidoFactory::addMelodyNoteDots(int dots)
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

    m_currentSymbol->setDots(dots);
}


QString BwwGuidoFactory::getGuidoCode()
{
    GuidoCodeVisitor codeVisitor;
    m_score->accept(&codeVisitor);

    return codeVisitor.guidoCode();
}
