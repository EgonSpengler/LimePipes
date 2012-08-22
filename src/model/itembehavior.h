/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ITEMBEHAVIOR_H
#define ITEMBEHAVIOR_H
#include <QMap>
#include <QVariant>

class ItemBehavior
{
public:
    enum Type {
        NoItemType = 1,
        RootItemType,
        ScoreType,
        TuneType,
        SymbolType
    };

    /*! Describees the valid DataRoles for Symbols */
    enum DataRole {
        //* Standard Music-Sheet-Roles */
        MusicSheetSymbol = Qt::UserRole + 1,/*!< The Symbol, as it appears in the MusicSheet (QIcon) */
        PitchRole = Qt::UserRole + 2,       /*!< The "vertical" appearance of the Symbol (Pitch) */
        LengthRole = Qt::UserRole + 3,      /*!< The "horizontal" appearance of the Symbol (Length) */

        /* Code-Roles */
        LimePipesCode = Qt::UserRole + 4,   /*!< The LimePipesCode for the Symbol (QString) */
        CustomCode = Qt::UserRole + 5       /*!< A custom Code appearance, e.g. BWW-code (QString) */
    };

    ItemBehavior(int type, int childType)
        : m_type(type), m_childType(childType) {}
    QVariant data(int role)
        { return m_data.value(role); }
    bool setData(const QVariant& value, int role)
        { m_data.insert(role, value); return true; }
    int type() const { return m_type; }
    int childType() const { return m_childType; }

private:
    QMap<int, QVariant> m_data;
    const int m_type;
    const int m_childType;
};

#endif // ITEMBEHAVIOR_H
