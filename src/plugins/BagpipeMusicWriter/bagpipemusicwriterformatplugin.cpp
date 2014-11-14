/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QDebug>

#include <parser.hpp>
#include "bagpipemusicwriterformatplugin.h"

BagpipeMusicWriterFormatPlugin::BagpipeMusicWriterFormatPlugin()
{
}

QString BagpipeMusicWriterFormatPlugin::formatName() const
{
    return QStringLiteral("Bagpipe Music Writer");
}

QString BagpipeMusicWriterFormatPlugin::fileNameFilter() const
{
    QString pattern("%1 (*.bmw *.bww)");
    return pattern.arg(formatName());
}

int BagpipeMusicWriterFormatPlugin::pluginOrder() const
{
    return 100;
}

QString BagpipeMusicWriterFormatPlugin::guidoCodeFromText(const QString &text, QStringList &errors)
{
    clearBwwFactory();
    setFlexBufferFromString(text);
    yyparse();
    return getGuidoCode();
}

