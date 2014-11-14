/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ITEXTFORMATPLUGIN_H
#define ITEXTFORMATPLUGIN_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QSyntaxHighlighter>

#include "iapplication.h"

class ITextFormatPlugin
{
public:
    ITextFormatPlugin() {}
    virtual ~ITextFormatPlugin() {}

    /*!
     * \brief formatName
     * \return The name of the format
     */
    virtual QString formatName() const = 0;

    /*!
     * \brief formatDescription
     * \return An optional description of the format (can contain html).
     */
    virtual QString formatDescription() const { return QString(); }

    /*!
     * \brief pluginOrder
     * \return The order of this plugin. The order describes e.g. the appearance in the
     * file open dialog. The Higher the number, the higher the order.
     */
    virtual int pluginOrder() const { return 0; }

    virtual void initialize(const IApplication *application) { Q_UNUSED(application); }

    /*!
     * \brief syntaxHighlighter
     * A factory method for a syntax highlighter for this format.
     * \return A syntax highlighter for this format.
     */
    virtual QSyntaxHighlighter *syntaxHighlighter() const { return nullptr; }

    /*!
     * \brief guidoCodeFromText
     * Convert a string from this specific format to guido code.
     * \param text The plain text as it will appear in the text editor.
     * \return The text converted into GUIDO notation format.
     */
    virtual QString guidoCodeFromText(const QString &text, QStringList &errors)
    {
        Q_UNUSED(text);
        errors << QObject::tr("Conversion to GUIDO format not supported by plugin");

        return QString();
    }

    /*!
     * \brief fileNameFilter
     * \return The filename filter, usable for a QFileDialog
     */
    virtual QString fileNameFilter() const { return QString(); }
};

#endif // ITEXTFORMATPLUGIN_H
