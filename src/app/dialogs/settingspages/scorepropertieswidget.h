/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCOREPROPERTIESWIDGET_H
#define SCOREPROPERTIESWIDGET_H

#include <QFont>
#include <QColor>
#include <QWidget>
#include <common/settingdefines.h>

namespace Ui {
class ScorePropertiesWidget;
}

class ScorePropertiesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScorePropertiesWidget(QWidget *parent = 0);
    ~ScorePropertiesWidget();

    void setText(const QString& text);

    void setAlignment(Settings::TextAlignment alignment);
    Settings::TextAlignment alignment() const;

    void setRow(int row);
    int row() const;

    void setFont(const QFont& font);
    QFont font() const;

    void setColor(const QColor& color);
    QColor color() const;

    bool isWidgetEnabled() const;
    void setWidgetEnabled(bool enabled);

signals:
    void fontChanged(const QFont& font);
    void colorChanged(const QColor& color);
    void rowChanged(int index);
    void alignmentChanged(Settings::TextAlignment alignment);
    void enabledChanged(bool enabled);

private slots:
    void fontChangeClicked();
    void colorChangeClicked();
    void newAlignmentSelected(int index);

private:
    void createConnections();
    Ui::ScorePropertiesWidget *ui;
};

#endif // SCOREPROPERTIESWIDGET_H
