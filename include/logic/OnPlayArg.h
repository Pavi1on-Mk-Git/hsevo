#ifndef ON_PLAY_ARG_H
#define ON_PLAY_ARG_H

#include <deque>
#include <fmt/format.h>
#include <ranges>
#include <variant>
#include <vector>

#include "TargetType.h"
#include "utils/GuiElementId.h"

template <class... Ts>
struct overloaded: Ts...
{
    using Ts::operator()...;
};

using OnPlayArg = std::variant<unsigned, TargetType>;

std::deque<GuiElementId> get_element_sequence(const std::vector<OnPlayArg>& args);

template <>
struct fmt::formatter<OnPlayArg>: formatter<std::string>
{
    auto format(const OnPlayArg& arg, format_context& ctx)
    {
        using enum TargetType;
        std::string name = std::visit(
            overloaded{
                [](const TargetType& type) -> std::string {
                    switch(type)
                    {
                    case ALLY_MINION:
                        return "ALLY_MINION";
                    case ALLY_HERO:
                        return "ALLY_HERO";
                    case ENEMY_MINION:
                        return "ENEMY_MINION";
                    case ENEMY_HERO:
                        return "ENEMY_HERO";
                    default:
                        return "UNKNOWN";
                    }
                },
                [](unsigned val) { return std::to_string(val); }
            },
            arg
        );
        return formatter<std::string>::format(name, ctx);
    }
};

template <>
struct fmt::formatter<std::vector<OnPlayArg>>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.begin();
    }

    auto format(const std::vector<OnPlayArg>& args, format_context& ctx)
    {
        if(args.empty())
            return fmt::format_to(ctx.out(), "");

        fmt::format_to(ctx.out(), " with args: ({}", args.at(0));
        for(const auto& arg: args | std::views::drop(1))
            fmt::format_to(ctx.out(), ", {}", arg);
        return fmt::format_to(ctx.out(), ")");
    }
};

#endif