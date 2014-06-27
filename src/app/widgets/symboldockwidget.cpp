/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "symboldockwidget.h"
#include "ui_symboldockwidget.h"

SymbolDockWidget::SymbolDockWidget(QWidget *parent)
    : QDockWidget(parent),
      ui(new Ui::SymbolDockWidget)
{
    ui->setupUi(this);
}

SymbolDockWidget::SymbolDockWidget(const QString &title, QWidget *parent)
    : QDockWidget(title, parent),
      ui(new Ui::SymbolDockWidget)
{
    ui->setupUi(this);
}

SymbolDockWidget::~SymbolDockWidget()
{
    delete ui;
}
