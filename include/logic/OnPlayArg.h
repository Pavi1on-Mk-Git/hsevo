#ifndef ON_PLAY_ARG_H
#define ON_PLAY_ARG_H

#include <deque>
#include <variant>
#include <vector>

#include "TargetType.h"
#include "utils/GuiElementId.h"

using OnPlayArg = std::variant<unsigned, TargetType>;

std::deque<GuiElementId> get_element_sequence(const std::vector<OnPlayArg>& args);

#endif