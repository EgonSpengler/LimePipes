/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef EMBELLISHMENTRULES_H
#define EMBELLISHMENTRULES_H

#include <QList>
#include <QObject>

#include "ast/AstDefines.h"

class QDir;
class Embellishment;

class EmbellishmentRules : public QObject
{
    Q_OBJECT
public:
    explicit EmbellishmentRules(QObject *parent = 0);

    void addRulesFromDirectory(const QDir &directory);

    QList<SymbolPitch> getAppearanceForEmbellishment(const Embellishment &embellishment);

private:
    void addRulesFromFile(const QString &fileName);
};

#endif // EMBELLISHMENTRULES_H
