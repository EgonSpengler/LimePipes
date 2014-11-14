/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GUIDOTEXTFORMATPLUGIN_H
#define GUIDOTEXTFORMATPLUGIN_H

#include <itextformatplugin.h>

class GuidoTextFormatPlugin : public ITextFormatPlugin
{
public:
    GuidoTextFormatPlugin();

    // ITextFormatPlugin interface
public:
    QString formatName() const;
    QString fileNameFilter() const;
    QString guidoCodeFromText(const QString &text, QStringList &errors);
};

#endif // GUIDOTEXTFORMATPLUGIN_H
