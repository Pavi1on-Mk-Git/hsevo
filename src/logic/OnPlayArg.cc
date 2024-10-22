#include "logic/OnPlayArg.h"

std::deque<GuiElementId> get_element_sequence(const std::vector<OnPlayArg>& args)
{
    std::deque<GuiElementId> sequence;
    for(unsigned arg_id = 0; arg_id < args.size(); ++arg_id)
    {
        if(std::holds_alternative<TargetType>(args.at(arg_id)))
        {
            const auto& type = std::get<TargetType>(args.at(arg_id));
            using enum TargetType;
            using enum GuiElementIdType;

            switch(type)
            {
            case ALLY_HERO:
                sequence.push_back(std::make_pair(HERO, true));
                break;
            case ENEMY_HERO:
                sequence.push_back(std::make_pair(HERO, false));
                break;
            case ALLY_MINION:
                arg_id++;
                sequence.push_back(std::make_tuple(MINION, true, std::get<unsigned>(args.at(arg_id))));
                break;
            case ENEMY_MINION:
                arg_id++;
                sequence.push_back(std::make_tuple(MINION, false, std::get<unsigned>(args.at(arg_id))));
                break;
            }
        }
    }
    return sequence;
}