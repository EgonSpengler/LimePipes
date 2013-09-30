/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALSCOREINTERFACE_H
#define VISUALSCOREINTERFACE_H

#include "graphicalscoreinterface.h"

class VisualScoreInterface
{
public:
    explicit VisualScoreInterface() {}
    virtual ~VisualScoreInterface() {}

    virtual GraphicalScoreInterface *graphicalScore() const = 0;
    virtual void setGraphicalScore(GraphicalScoreInterface *graphicalScore) = 0;
};

#endif // VISUALSCOREINTERFACE_H
