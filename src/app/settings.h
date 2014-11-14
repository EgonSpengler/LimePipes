/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class QSettings;

class Settings : public QObject
{
public:
    explicit Settings(QObject *parent = 0);

    QString fileOpenSavePath() const;
    void setFileOpenSavePath(const QString &path);

private:
    QSettings *m_settings;
};

#endif // SETTINGS_H
