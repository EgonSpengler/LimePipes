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

    double spaceAboveStaff() const;
    void setSpaceAboveStaff(double spaceAboveStaff);

signals:
    void layoutChanged();

private:
    double m_spaceAboveStaff;
};
typedef QSharedPointer<MusicLayout> MusicLayoutPtr;

#endif // MUSICLAYOUT_H
