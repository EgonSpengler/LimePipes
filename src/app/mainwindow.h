/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QMap>

namespace Ui {
class MainWindow;
}

class GuidoWidget;
class TextEditHeaderWidget;
class IApplication;
class ITextFormatPlugin;
class Settings;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void refreshGuidoWidget();
    void on_actionOpen_triggered();
    void on_actionExportToSvg_triggered();

private:
    void createConnections();
    void loadPlugins();
    Ui::MainWindow *ui;
    GuidoWidget *m_guidoWidget;
    IApplication *m_application;
    TextEditHeaderWidget *m_textEditHeaderWidget;
    QHash<QString, ITextFormatPlugin*> m_plugins;
    QMap<int, QString> m_pluginOrders;
    Settings *m_settings;
};

#endif // MAINWINDOW_H
