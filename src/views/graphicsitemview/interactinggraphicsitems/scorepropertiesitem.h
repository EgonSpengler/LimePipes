/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCOREPROPERTIESITEM_H
#define SCOREPROPERTIESITEM_H

#include "../scorepropertiesinterface.h"
#include "interactinggraphicsitem.h"

class ScorePropertiesItem : public ScorePropertiesInterface,
                            public InteractingGraphicsItem
{
public:
    explicit ScorePropertiesItem();
    virtual ~ScorePropertiesItem() {}

    // ScorePropertiesInterface interface
public:
    QString title() const;
    void setTitle(const QString &title);
    QString composer() const;
    void setComposer(const QString &composer);

private:
    QString m_title;
    QString m_composer;
};

#endif // SCOREPROPERTIESITEM_H
