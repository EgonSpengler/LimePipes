/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCOREPROPERTIESINTERFACE_H
#define SCOREPROPERTIESINTERFACE_H

#include <datatypes/timesignature.h>

class QString;

class ScorePropertiesInterface
{
public:
    explicit ScorePropertiesInterface() {}
    virtual ~ScorePropertiesInterface() {}

    virtual QString title() const = 0;
    virtual void setTitle(const QString& title) = 0;

    virtual QString type() const = 0;
    virtual void setType(const QString& type) = 0;

    virtual QString composer() const = 0;
    virtual void setComposer(const QString& composer) = 0;

    virtual QString arranger() const = 0;
    virtual void setArranger(const QString& arranger) = 0;

    virtual QString year() const = 0;
    virtual void setYear(const QString& year) = 0;

    virtual QString copyright() const = 0;
    virtual void setCopyright(const QString& copyright) = 0;
};

#endif // SCOREPROPERTIESINTERFACE_H
