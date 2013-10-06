/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ABSTRACTSCOREPROPERTIESITEMDUMMY_H
#define ABSTRACTSCOREPROPERTIESITEMDUMMY_H

#include <graphicsitemview/abstractscorepropertiesitem.h>

class AbstractScorePropertiesItemDummy :  public AbstractScorePropertiesItem
{
    Q_OBJECT
public:
    explicit AbstractScorePropertiesItemDummy(QObject *parent = 0);

signals:
    void setNewTitleCalled();
    void setNewComposerCalled();
    void setNewArrangerCalled();
    void setNewYearCalled();
    void setNewCopyrightCalled();
    void setNewTimeSignatureCalled();

    // AbstractScorePropertiesItem interface
public slots:
    void setNewTitle(const QString &title);
    void setNewComposer(const QString &composer);
    void setNewArranger(const QString &arranger);
    void setNewYear(const QString &year);
    void setNewCopyright(const QString &copyright);
    void setNewTimeSignature(const TimeSignature &timeSig);
};

#endif // ABSTRACTSCOREPROPERTIESITEMDUMMY_H
