/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef BAGPIPEMUSICWRITERFORMATPLUGIN_H
#define BAGPIPEMUSICWRITERFORMATPLUGIN_H

#include <itextformatplugin.h>

class BagpipeMusicWriterFormatPlugin : public ITextFormatPlugin
{
public:
    BagpipeMusicWriterFormatPlugin();

    // ITextFormatPlugin interface
public:
    QString formatName() const;
    QString fileNameFilter() const;
    int pluginOrder() const;
    QString guidoCodeFromText(const QString &text, QStringList &errors);
};

#endif // BAGPIPEMUSICWRITERFORMATPLUGIN_H
