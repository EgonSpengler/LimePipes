/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "zoomwidget.h"
#include "ui_zoomwidget.h"

ZoomWidget::ZoomWidget(QWidget *parent)
    : QFrame(parent),
      ui(new Ui::ZoomWidget)
{
    ui->setupUi(this);

    setDisplayedZoomLevel(ui->zoomSlider->value());
    connect(ui->zoomSlider, &QSlider::valueChanged,
            [this] (int value){
        setDisplayedZoomLevel(value);
    });

    connect(ui->zoomSlider, &QSlider::valueChanged,
            [this] (int value) {
        emit zoomLevelChanged((qreal)value / 100);
    });
}

ZoomWidget::~ZoomWidget()
{
    delete ui;
}

void ZoomWidget::setDisplayedZoomLevel(int level)
{
    ui->zoomLevelLabel->setText(QString("%1%")
                                .arg(level));
}
