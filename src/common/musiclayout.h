/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICLAYOUT_H
#define MUSICLAYOUT_H

#include <QObject>
#include <QSharedPointer>

class MusicLayout : public QObject
{
    Q_OBJECT
public:
    explicit MusicLayout(QObject *parent = 0);

    double staffSpacing() const;
    void setStaffSpacing(double staffSpacing);

signals:
    void layoutChanged();

private:
    double m_staffSpacing;
};
typedef QSharedPointer<MusicLayout> MusicLayoutPtr;

#endif // MUSICLAYOUT_H
