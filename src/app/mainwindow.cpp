/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */
#include <fstream>

#include <QDebug>
#include <QScrollArea>
#include <QPageSize>
#include <QFileDialog>
#include <QMessageBox>

#include <QGuidoPainter.h>
#include <GUIDOEngine.h>

#include <itextformatplugin.h>
// Plugins
#include <Guido/guidotextformatplugin.h>
#include <BagpipeMusicWriter/bagpipemusicwriterformatplugin.h>

#include "settings.h"
#include "texteditheaderwidget.h"
#include "application.h"
#include "guidowidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_application = new Application();
    m_textEditHeaderWidget = new TextEditHeaderWidget;
    m_settings = new Settings(this);
    ui->textDockWidget->setTitleBarWidget(m_textEditHeaderWidget);

    QGuidoPainter::startGuidoEngine();
    m_guidoWidget = new GuidoWidget();

    ui->scrollArea->setWidget(m_guidoWidget);

    createConnections();
    loadPlugins();

    foreach (const QString &pluginName, m_plugins.keys()) {
        m_textEditHeaderWidget->addTextPluginName(pluginName);
    }
}

void MainWindow::createConnections()
{
    connect(ui->actionViewRefresh, &QAction::triggered,
            this, &MainWindow::refreshGuidoWidget);

    connect(ui->textEdit, &QPlainTextEdit::modificationChanged,
            this, &MainWindow::refreshGuidoWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_application;
}

void MainWindow::refreshGuidoWidget()
{
    qDebug() << "refresh view";
    QString plainText = ui->textEdit->toPlainText();
    QString currentTextPlugin = m_textEditHeaderWidget->selectedTextPluginName();
    ITextFormatPlugin *formatPlugin = m_plugins.value(currentTextPlugin);
    if (!formatPlugin) {
        qWarning() << "Textformat plugin not loaded: " << currentTextPlugin;
        return;
    }

    QStringList errorMessages;
    QString guidoText = formatPlugin->guidoCodeFromText(plainText, errorMessages);
    ui->debugTextEdit->setPlainText(guidoText);

    if (errorMessages.count()) {
        QMessageBox::warning(this, tr("Failed update music sheet"),
                             QString("%1:\n- %2")
                             .arg(tr("Failed updating the music sheet with code from text edit"))
                             .arg(errorMessages.join("\n- ")), QMessageBox::Ok);
        return;
    }

    if (m_guidoWidget->setGMNCode(guidoText, QStringLiteral(""))) {
        int pageNr = m_guidoWidget->firstVisiblePage();
        QSizeF guidoPageSizeMM = m_guidoWidget->pageSizeMM(pageNr);
        QPageSize pageSize(guidoPageSizeMM, QPageSize::Millimeter, QString(),
                           QPageSize::FuzzyOrientationMatch);
        qDebug() << "Code has page count: " << m_guidoWidget->pageCount();
        m_guidoWidget->setPage( pageNr );
        m_guidoWidget->resize( pageSize.sizePixels(100) );
    } else {
        qDebug() << "Error setting code: " << m_guidoWidget->getLastErrorMessage();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QStringList fileNameFilters;
    foreach (const QString &pluginName, m_pluginOrders) {
        const ITextFormatPlugin *plugin = m_plugins.value(pluginName);
        fileNameFilters << plugin->fileNameFilter();
    }

    QFileDialog fileDialog;
    QString fileOpenSavePath = m_settings->fileOpenSavePath();
    if (!fileOpenSavePath.isEmpty()) {
        fileDialog.setDirectory(m_settings->fileOpenSavePath());
    }
    fileDialog.setNameFilters(fileNameFilters);
    fileDialog.setFileMode(QFileDialog::ExistingFile);

    if (!fileDialog.exec()) {
        return;
    }

    m_settings->setFileOpenSavePath(fileDialog.directory().absolutePath());

    QStringList selectedFiles = fileDialog.selectedFiles();
    QFileInfo selectedFile(selectedFiles.first());
    QString fileExtension = selectedFile.suffix();

    ITextFormatPlugin *textPlugin = 0;
    foreach (ITextFormatPlugin *plugin, m_plugins) {
        if (plugin->fileNameFilter().contains(fileExtension)) {
            textPlugin = plugin;
        }
    }

    if (textPlugin == 0) {
        return;
    }

    QFile openFile(selectedFile.absoluteFilePath());
    if (!openFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open file for reading: " << selectedFile.absoluteFilePath();
        return;
    }

    QString fileContent(openFile.readAll());
    openFile.close();
    ui->textEdit->setPlainText(fileContent);
    m_textEditHeaderWidget->selectTextPluginName(textPlugin->formatName());

    refreshGuidoWidget();
}

void MainWindow::on_actionExportToSvg_triggered()
{
    QString exportFileName = QFileDialog::getSaveFileName(this, tr("Export to svg"),
                                                          QDir::homePath(),
                                                          tr("Scalable Vector Graphics (*.svg)"));

    if (exportFileName.isEmpty()) {
        return;
    }

    std::ofstream outStream;
    outStream.open(exportFileName.toUtf8().constData());
    GuidoSVGExport(const_cast<GRHandler>(m_guidoWidget->getGRHandler()), 1, outStream, Q_NULLPTR);
    outStream.close();
}

/*!
 * \brief MainWindow::loadPlugins
 * Plugins should be later loaded via Qt Plugin system
 */
void MainWindow::loadPlugins()
{
    ITextFormatPlugin *textPlugin = new BagpipeMusicWriterFormatPlugin();
    if (!textPlugin->formatName().isEmpty()) {
        m_pluginOrders.insert(-1 * textPlugin->pluginOrder(), textPlugin->formatName());
        m_plugins.insert(textPlugin->formatName(), textPlugin);
    }

    textPlugin = new GuidoTextFormatPlugin();
    if (!textPlugin->formatName().isEmpty()) {
        m_pluginOrders.insert(-1 * textPlugin->pluginOrder(), textPlugin->formatName());
        m_plugins.insert(textPlugin->formatName(), textPlugin);
    }
}
