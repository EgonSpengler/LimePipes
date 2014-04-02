/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SMUFLTYPES_H
#define SMUFLTYPES_H

#include <QPointF>

struct Engravings {
    qreal arrowShaftThickness;
    qreal barlineSeparation;
    qreal beamSpacing;
    qreal beamThickness;
    qreal bracketThickness;
    qreal dashedBarlineDashLength;
    qreal dashedBarlineGapLength;
    qreal dashedBarlineThickness;
    qreal hairpinThickness;
    qreal legerLineExtension;
    qreal legerLineThickness;
    qreal lyricLineThickness;
    qreal octaveLineThickness;
    qreal pedalLineThickness;
    qreal repeatBarlineDotSeparation;
    qreal repeatEndingLineThickness;
    qreal slurEndpointThickness;
    qreal slurMidpointThickness;
    qreal staffLineThickness;
    qreal stemThickness;
    qreal subBracketThickness;
    qreal textEnclosureThickness;
    qreal thickBarlineThickness;
    qreal thinBarlineThickness;
    qreal tieEndpointThickness;
    qreal tieMidpointThickness;
    qreal tupletBracketThickness;
};

struct GlyphData {
    GlyphData() : nominalWidth(0) {}
    QPointF stemUpSE;
    QPointF stemDownNW;
    QPointF stemUpNW;
    QPointF stemDownSW;
    qreal nominalWidth;
    QPointF numeralTop;
    QPointF numeralBottom;
};

#endif // SMUFLTYPES_H
