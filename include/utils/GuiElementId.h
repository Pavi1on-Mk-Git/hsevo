#ifndef GUI_ELEMENT_ID_H
#define GUI_ELEMENT_ID_H

#include <tuple>
#include <variant>

enum class GuiElementIdType
{
    HERO,
    HERO_POWER,
    MINION,
    CARD,
    EOT_BUTTON
};

using GuiElementIdRegular = std::pair<GuiElementIdType, bool>;
using GuiElementIdWithPosition = std::tuple<GuiElementIdType, bool, unsigned>;
using GuiElementEOT = GuiElementIdType;

using GuiElementId = std::variant<GuiElementIdRegular, GuiElementIdWithPosition, GuiElementEOT>;

#endif