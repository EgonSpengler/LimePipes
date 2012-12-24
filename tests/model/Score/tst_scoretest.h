/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */
#ifndef SCORETEST_H
#define SCORETEST_H

#include <QObject>
#include <score.h>

class ScoreTest : public QObject
{
    Q_OBJECT
    
public:
    ScoreTest() : m_score(0) {}
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testType();
    void testChildType();
    void testSetData();
    void testConstructor();
    void testSetGetTitle();
    void testWriteToXmlStream();
    void testReadFromXmlStream();

private:
    void readTextElement(const QString &tagName, const QString &elementText);
    void readTimeSignatureElement(TimeSignature::Type type);
    void readString(const QString &string);
    QString patternForTag(const QString &tagname, const QString &data);
    Score *m_score;
};

#endif
