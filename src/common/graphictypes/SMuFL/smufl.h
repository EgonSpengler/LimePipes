/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SMUFL_H
#define SMUFL_H

#include <QFont>
#include "smufltypes.h"

class SMuFL
{
public:
    SMuFL();
    virtual ~SMuFL();

    static SMuFL *instance();

    virtual QFont font() const;

    virtual quint32 codepointForGlyph(const QString& glyphname) const;
    virtual quint32 alternateCodepointForGlyph(const QString& glyphname) const;
    virtual Engravings engravings() const;
    virtual GlyphData glyphData(const QString& glyphname);

protected:
    static SMuFL *m_smufl;
};

#endif // SMUFL_H
