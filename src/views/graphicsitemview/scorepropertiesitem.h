/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCOREPROPERTIESITEM_H
#define SCOREPROPERTIESITEM_H

#include <QObject>
#include <QString>
#include "scorepropertiesinterface.h"

class ScorePropertiesItem : public QObject,
                            public ScorePropertiesInterface
{
    Q_OBJECT
public:
    explicit ScorePropertiesItem(QObject *parent = 0);
    ~ScorePropertiesItem() {}

    void linkWithItem(ScorePropertiesItem *item);
    const ScorePropertiesItem *linkedItem() const;

signals:
    void titleChanged(const QString& newTitle);
    void typeChanged(const QString & newType);
    void composerChanged(const QString& newComposer);
    void arrangerChanged(const QString& newArranger);
    void yearChanged(const QString& newYear);
    void copyrightChanged(const QString& newCopyright);

public slots:
    void setTitle(const QString &title);
    void setType(const QString &type);
    void setComposer(const QString &composer);
    void setArranger(const QString &arranger);
    void setYear(const QString &year);
    void setCopyright(const QString &copyright);

public:
    QString title() const;
    QString type() const;
    QString composer() const;
    QString arranger() const;
    QString year() const;
    QString copyright() const;

private:
    QString m_title;
    QString m_type;
    QString m_composer;
    QString m_arranger;
    QString m_year;
    QString m_copyright;
    const ScorePropertiesItem *m_linkedItem;
};

#endif // SCOREPROPERTIESITEM_H
