/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SETTINGDEFINES_H
#define SETTINGDEFINES_H

#include <QVariant>
#include <itemdatatypes.h>

namespace Settings
{

enum class TextAlignment
{
    NoAlignment,
    Left,
    Center,
    Right
};

// Score
namespace Score {

enum Area {
    Header,
    Footer
};

enum Appearance {
    Enabled,
    Font,
    Color,
    Row,
    Alignment
};

} // namespace Score

} // namespace Settings

Q_DECLARE_METATYPE(Settings::TextAlignment)

#endif // SETTINGDEFINES_H
