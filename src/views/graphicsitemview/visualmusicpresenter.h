/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALMUSICPRESENTER_H
#define VISUALMUSICPRESENTER_H

#include <QObject>

class VisualMusicPresenter : public QObject
{
    friend class VisualMusicPresenterTest;
public:
    explicit VisualMusicPresenter(QObject *parent = 0);

};

#endif // VISUALMUSICPRESENTER_H
