/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "testsymbolgraphicbuilder.h"

TestSymbolGraphicBuilder::TestSymbolGraphicBuilder(QObject *parent)
    : QObject(parent)
{
}

void TestSymbolGraphicBuilder::setGraphicDataRoles(const QVector<int> &roles)
{
    m_graphicDataRoles = roles;
}

void TestSymbolGraphicBuilder::updateSymbolGraphic(const QVariant &value, int key)
{
    emit updateSymbolGraphicCalled();
}

QVector<int> TestSymbolGraphicBuilder::graphicDataRoles() const
{
    return m_graphicDataRoles;
}

void TestSymbolGraphicBuilder::initializeSymbolGraphic()
{
    emit initSymbolGraphicCalled();
}
