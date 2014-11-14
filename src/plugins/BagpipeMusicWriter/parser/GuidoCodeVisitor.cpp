/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QStringList>
#include <QDebug>

#include "ast/melodynote.h"
#include "GuidoCodeVisitor.h"

static const QString TitleTemplate(QStringLiteral("\\title<\"%1\">"));

QHash<SymbolPitch, QString>
GuidoCodeVisitor::s_melodyNotePitchMap(GuidoCodeVisitor::initMelodyNotePitchMap());

QHash<SymbolPitch, QString> GuidoCodeVisitor::initMelodyNotePitchMap()
{
    QHash<SymbolPitch, QString> pitchMap;
    pitchMap.insert(LowG, QStringLiteral("g1"));
    pitchMap.insert(LowA, QStringLiteral("a1"));
    pitchMap.insert(B, QStringLiteral("b1"));
    pitchMap.insert(C, QStringLiteral("c#2"));
    pitchMap.insert(D, QStringLiteral("d2"));
    pitchMap.insert(E, QStringLiteral("e2"));
    pitchMap.insert(F, QStringLiteral("f#2"));
    pitchMap.insert(HighG, QStringLiteral("g2"));
    pitchMap.insert(HighA, QStringLiteral("a2"));
    return pitchMap;
}

GuidoCodeVisitor::GuidoCodeVisitor()
{
}

void GuidoCodeVisitor::visit(Score *score)
{
    qDebug() << "Visit Score";
    m_guidoCode.append(QStringLiteral("{[\n"));
    QStringList headerParts;
    headerParts.append(QStringLiteral("\\staff<1>"));
    headerParts.append(QStringLiteral("\\clef<\"g2\">"));
    headerParts.append(QStringLiteral("\\key<2>"));
    headerParts.append(QStringLiteral("\\stemsDown"));

    m_guidoCode.append(headerParts.join(QLatin1Char(' ')));

}

void GuidoCodeVisitor::finishVisit(Score *score)
{
    qDebug() << "Finish visit Score";
    m_guidoCode.append(QStringLiteral("\n]}"));
}

void GuidoCodeVisitor::visit(Tune *tune)
{
    qDebug() << "Visit Tune";
    MusicItem *tuneParent = tune->parent();
    int tuneIndex = tuneParent->children().indexOf(tune);
    if (tuneIndex == 0) {
        m_guidoCode.append(TitleTemplate.arg(tune->title));
    }
}

void GuidoCodeVisitor::finishVisit(Tune *tune)
{
    qDebug() << "Finish visit Tune";
}

void GuidoCodeVisitor::visit(Part *part)
{
    qDebug() << "Visit Part";
}

void GuidoCodeVisitor::finishVisit(Part *part)
{
    qDebug() << "Finish visit Part";
}

void GuidoCodeVisitor::visit(Symbol *symbol)
{
    qDebug() << "Visit Symbol";
    switch (symbol->type()) {
    case T_Melody: {
        MelodyNote *note = static_cast<MelodyNote*>(symbol);
        if (note) {
            addMelodyNote(note);
        }
        break;
    }
    case T_Bar: {
        m_guidoCode.append(QStringLiteral("\\bar"));
        break;
    }
    default:
        qWarning() << "Symbol type not handled: " << symbol->type();
        break;
    }
}

void GuidoCodeVisitor::addMelodyNote(MelodyNote *note)
{
    QString noteTemplate(QStringLiteral("%1/%2"));
    noteTemplate = noteTemplate.arg(s_melodyNotePitchMap.value(note->pitch()))
                                    .arg(note->length());
    if (note->dots() > 0) {
        for (int i=0; i<note->dots(); ++i) {
            noteTemplate.append(QLatin1Char('.'));
        }
    }
    m_guidoCode.append(noteTemplate);
}

void GuidoCodeVisitor::finishVisit(Symbol *symbol)
{
    qDebug() << "Finish visit Symbol";
}

QString GuidoCodeVisitor::guidoCode() const
{
    return m_guidoCode.join(QLatin1Char(' '));
}


