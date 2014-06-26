/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ZOOMWIDGET_H
#define ZOOMWIDGET_H

#include <QFrame>

namespace Ui {
class ZoomWidget;
}

class ZoomWidget : public QFrame
{
    Q_OBJECT

public:
    explicit ZoomWidget(QWidget *parent = 0);
    ~ZoomWidget();

signals:
    void zoomLevelChanged(qreal level);

private:
    void setDisplayedZoomLevel(int level);
    Ui::ZoomWidget *ui;
};

#endif // ZOOMWIDGET_H
