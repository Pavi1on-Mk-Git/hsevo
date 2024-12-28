#ifndef GUI_ELEMENT_ID_H
#define GUI_ELEMENT_ID_H

#include <tuple>
#include <variant>

/**
 * Type of a clickable element present in the gui
 */
enum class GuiElementIdType
{
    HERO,
    HERO_POWER,
    MINION,
    CARD,
    EOT_BUTTON,
    DISCOVER,
    OTHER,
};

/**
 * Element which belongs to one side of the screen
 */
using GuiElementIdSided = std::pair<GuiElementIdType, bool>;

/**
 * Element which belongs to one side of the screen and has a position
 */
using GuiElementIdWithPosition = std::tuple<GuiElementIdType, bool, unsigned>;

/**
 * Element which exists independently of screen side
 */
using GuiElementIdRegular = GuiElementIdType;

/**
 * Element which exists independently of screen side and has a position
 */
using GuiElementDiscover = std::pair<GuiElementIdType, unsigned>;

using GuiElementId = std::variant<GuiElementIdSided, GuiElementIdWithPosition, GuiElementIdRegular, GuiElementDiscover>;

#endif