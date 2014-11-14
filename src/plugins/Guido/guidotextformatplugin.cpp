/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "guidotextformatplugin.h"

GuidoTextFormatPlugin::GuidoTextFormatPlugin()
{
}

QString GuidoTextFormatPlugin::formatName() const
{
    return QStringLiteral("GUIDO Music Notation");
}

QString GuidoTextFormatPlugin::fileNameFilter() const
{
    QString pattern("%1 (*.gmn)");
    return pattern.arg(formatName());
}

QString GuidoTextFormatPlugin::guidoCodeFromText(const QString &text, QStringList &errors)
{
    Q_UNUSED(errors);
    return text;
}
