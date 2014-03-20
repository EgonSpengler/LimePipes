/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TESTSYMBOLGRAPHICBUILDER_H
#define TESTSYMBOLGRAPHICBUILDER_H

#include <QObject>
#include <src/common/graphictypes/symbolgraphicbuilder.h>

class TestSymbolGraphicBuilder : public QObject,
                                 public SymbolGraphicBuilder
{
    Q_OBJECT
public:
    explicit TestSymbolGraphicBuilder(QObject *parent = 0);

    void setGraphicDataRoles(const QVector<int>& roles);

signals:
    void updateSymbolGraphicCalled();
    void initSymbolGraphicCalled();

    // SymbolGraphicBuilder interface
public:
    void updateSymbolGraphic(const QVariant &value, int key);
    QVector<int> graphicDataRoles() const;
    void initSymbolGraphic();

private:
    QVector<int> m_graphicDataRoles;
};

#endif // TESTSYMBOLGRAPHICBUILDER_H
