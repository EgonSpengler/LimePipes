/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SETTINGDEFINES_H
#define SETTINGDEFINES_H

#include <QFont>
#include <QColor>

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
static QString TitleFontKey("score title font");
static QFont   TitleFontDefault("Arial", 18);
}

}

#endif // SETTINGDEFINES_H
