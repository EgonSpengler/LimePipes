/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QDebug>

#include "EmbellishmentContextVisitor.h"

EmbellishmentContextVisitor::EmbellishmentContextVisitor()
{
}

EmbellishmentContextVisitor::~EmbellishmentContextVisitor()
{
}

void EmbellishmentContextVisitor::visit(Score *score)
{

}

void EmbellishmentContextVisitor::visit(Tune *tune)
{

}

void EmbellishmentContextVisitor::visit(Part *part)
{

}

void EmbellishmentContextVisitor::visit(Symbol *symbol)
{
    qDebug() << "EmbellishmentContextVisitor: Visit symbol";
}

void EmbellishmentContextVisitor::finishVisit(Score *score)
{

}

void EmbellishmentContextVisitor::finishVisit(Tune *tune)
{

}

void EmbellishmentContextVisitor::finishVisit(Part *part)
{

}

void EmbellishmentContextVisitor::finishVisit(Symbol *symbol)
{

}
