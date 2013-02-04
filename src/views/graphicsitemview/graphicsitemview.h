/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GRAPHICSITEMVIEW_H
#define GRAPHICSITEMVIEW_H

#include <QAbstractItemView>

class GraphicsItemView : public QAbstractItemView
{
    Q_OBJECT
public:
    explicit GraphicsItemView(QWidget *parent = 0);
};

#endif // GRAPHICSITEMVIEW_H
