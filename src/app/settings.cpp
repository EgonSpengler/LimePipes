/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QSettings>

#include "settings.h"

static const QString FileOpenSavePathKey("file open path");

Settings::Settings(QObject *parent)
    : QObject(parent)
{
    m_settings = new QSettings(this);
}

QString Settings::fileOpenSavePath() const
{
    return m_settings->value(FileOpenSavePathKey, QString()).toString();
}

void Settings::setFileOpenSavePath(const QString &path)
{
    m_settings->setValue(FileOpenSavePathKey, path);
}
