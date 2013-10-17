/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QGraphicsWidget>

class GraphicsTextItem;

class TextWidget : public QGraphicsWidget
{
    Q_OBJECT
public:
    explicit TextWidget(QGraphicsItem *parent = 0);

    void setText(const QString& text);
    QString text() const;

signals:
    void textChanged(const QString& text);

private slots:
    void textItemBlockCountChanged();
    void textItemFocusIn();
    void textItemFocusOut();

private:
    void createConnections();
    void resizeEvent(QGraphicsSceneResizeEvent *event);
    GraphicsTextItem *m_textItem;
    QString m_textBeforeEdit;
};

#endif // TEXTWIDGET_H
