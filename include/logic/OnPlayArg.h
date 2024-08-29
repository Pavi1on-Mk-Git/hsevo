#ifndef ON_PLAY_ARG_H
#define ON_PLAY_ARG_H

#include <variant>

#include "TargetType.h"

using OnPlayArg = std::variant<unsigned, TargetType>;

#endif