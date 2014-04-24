/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MELODYNOTETEST_H
#define MELODYNOTETEST_H

#include <QObject>
#include <plugins/IntegratedSymbols/symbols/melodynote.h>

class MelodyNoteTest : public QObject
{
    Q_OBJECT

public:
    MelodyNoteTest()
        : m_melody(0) {}

private Q_SLOTS:
    void init();
    void cleanup();
    void testDefaultConstructor();
    void testTypeAndNameConstructor();
    void testDots();
    void testWriteItemDataToStream();
    void testReadFromXmlStream();

private:
    void readTextElement(const QString &tagName, const QString &elementText);
    void readString(const QString &string);
    QString tagString(const QString &tagname, const QString &data);
    MelodyNote *m_melody;
};

#endif
