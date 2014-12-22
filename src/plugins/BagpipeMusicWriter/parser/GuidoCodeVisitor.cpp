/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QDir>
#include <QStringList>
#include <QDebug>

#include "ast/melodynote.h"
#include "ast/timesignature.h"
#include "ast/embellishment.h"
#include "EmbellishmentRules.h"
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
    : m_embellishmentRules(Q_NULLPTR)
{
}

GuidoCodeVisitor::~GuidoCodeVisitor()
{
}

void GuidoCodeVisitor::visit(Score *score)
{
//    qDebug() << "Visit Score";
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
//    qDebug() << "Finish visit Score";
    m_guidoCode.append(QStringLiteral("\n]}"));
}

void GuidoCodeVisitor::visit(Tune *tune)
{
//    qDebug() << "Visit Tune";
    MusicItem *tuneParent = tune->parent();
    int tuneIndex = tuneParent->children().indexOf(tune);
    if (tuneIndex == 0) {
        m_guidoCode.append(TitleTemplate.arg(tune->title));
    }
}

void GuidoCodeVisitor::finishVisit(Tune *tune)
{
//    qDebug() << "Finish visit Tune";
}

void GuidoCodeVisitor::visit(Part *part)
{
//    qDebug() << "Visit Part";
}

void GuidoCodeVisitor::finishVisit(Part *part)
{
//    qDebug() << "Finish visit Part";
}

void GuidoCodeVisitor::visit(Symbol *symbol)
{
//    qDebug() << "Visit Symbol";
    switch (symbol->type()) {
    case T_TimeSignature: {
        TimeSignature * timeSig = static_cast<TimeSignature*>(symbol);
        if (timeSig) {
            addTimeSignature(timeSig);
        }
        break;
    }
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
    case T_Embellishment: {
        Embellishment *embellishment = static_cast<Embellishment*>(symbol);
        if (embellishment) {
            addEmbellishment(*embellishment);
        }
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

void GuidoCodeVisitor::addTimeSignature(TimeSignature *time)
{
    QString meterTemplate(QStringLiteral("\\meter<\"%1/%2\">"));
    if (time->showAsSymbol()) {
        if (time->beatCount() == 2 &&
                time->beatUnit() == 2) {
            m_guidoCode.append(QStringLiteral("\\meter<\"C/\">"));
            return;
        }
        if (time->beatCount() == 4 &&
                time->beatUnit() == 4) {
            m_guidoCode.append(QStringLiteral("\\meter<\"C\">"));
            return;
        }
    }

    m_guidoCode.append(meterTemplate.arg(time->beatCount())
                       .arg(time->beatUnit()));
}

void GuidoCodeVisitor::addEmbellishment(const Embellishment &embellishment)
{
    if (!m_embellishmentRules) {
        qWarning() << "Can't add embellishment with no embellishment rules set!";
        return;
    }

    addGraceSequence(m_embellishmentRules->getAppearanceForEmbellishment(embellishment));
}

void GuidoCodeVisitor::addGraceSequence(const QList<SymbolPitch> &pitches)
{
    if (!pitches.count()) {
        return;
    }
    if (pitches.contains(NoPitch)) {
        qWarning() << "Embellishment contains invalid pitch (NoPitch).";
        return;
    }

    QString codeTemplate;
    if (pitches.count() == 1) {
        // No need for beam
        codeTemplate = QStringLiteral("\\stemsUp \\grace( %1 ) \\stemsDown");
    } else {
        codeTemplate = QStringLiteral("\\stemsUp \\beam( \\grace( %1 )) \\stemsDown");
    }

    QStringList embellishmentItems;
    foreach (const SymbolPitch &pitch, pitches) {
        if (embellishmentItems.isEmpty()) {
            // first element
            embellishmentItems.append(s_melodyNotePitchMap.value(pitch) + QStringLiteral("/32"));
        } else {
            embellishmentItems.append(s_melodyNotePitchMap.value(pitch));
        }
    }

    m_guidoCode.append(codeTemplate.arg(embellishmentItems.join(QLatin1Char(' '))));
}

void GuidoCodeVisitor::setEmbellishmentRules(EmbellishmentRules *embellishmentRules)
{
    m_embellishmentRules = embellishmentRules;
}

void GuidoCodeVisitor::finishVisit(Symbol *symbol)
{
    //    qDebug() << "Finish visit Symbol";
}

QString GuidoCodeVisitor::guidoCode() const
{
    return m_guidoCode.join(QLatin1Char(' '));
}


