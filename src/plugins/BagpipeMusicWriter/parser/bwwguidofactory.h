/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef BWWGUIDOFACTORY_H
#define BWWGUIDOFACTORY_H

#include <QString>
#include <QStringList>
#include <QList>

class Score;
class Tune;
class Part;
class Symbol;

class BwwGuidoFactory
{
public:
    explicit BwwGuidoFactory();
    ~BwwGuidoFactory();

    void clear();

    void setTitle(const QString &title);
    void addMelodyNote(const QString &bwwCode);
    void addMelodyNoteDots(int dots);
    void addBarline();
    void endPart(bool repeat);
    void addTimeSignature(const QString &bwwCode);

    QString getGuidoCode();
private:
    void initAst();

    Score *m_score;
    Tune *m_currentTune;
    Part *m_currentPart;
    Symbol *m_currentSymbol;
};

#endif // BWWGUIDOFACTORY_H
