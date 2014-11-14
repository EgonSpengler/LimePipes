/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GUIDOWIDGET_H
#define GUIDOWIDGET_H

#include <QGuidoWidget.h>

class GuidoWidget : public QGuidoWidget
{
    Q_OBJECT
public:
    explicit GuidoWidget(QWidget *parent = 0);
};

#endif // GUIDOWIDGET_H
