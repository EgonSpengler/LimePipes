#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../model/model.h"
#include "bar.h"
#include "melodynote.h"

/* Debug */
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_model = new Model();
    ui->listView->setModel(m_model);

    QStandardItem *item = new QStandardItem();
    item->setIcon(QIcon(":/application/resources/img/application.svg"));
    item->setToolTip("fresh");

    m_model->appendRow( new Bar());
    m_model->appendRow( new MelodyNote());
    m_model->appendRow( new Bar());

}

void MainWindow::appendSymbol(Symbol *sym)
{
    QList<QStandardItem *> itemList;
    itemList.append(sym);
    if( sym->pitch() != 0)
    {
        itemList.append(sym->pitch());
    }
    m_model->appendRow(itemList);
}

MainWindow::~MainWindow()
{
    delete ui;
}
