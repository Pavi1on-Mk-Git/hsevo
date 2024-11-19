#include "logic/OnPlayArg.h"

std::deque<GuiElementId> get_element_sequence(const std::vector<OnPlayArg>& args)
{
    std::deque<GuiElementId> sequence;
    for(auto arg = args.begin(); arg != args.end(); ++arg)
    {
        if(std::holds_alternative<TargetType>(*arg))
        {
            const auto& type = std::get<TargetType>(*arg);
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
                sequence.push_back(std::make_tuple(MINION, true, std::get<unsigned>(*(++arg))));
                break;
            case ENEMY_MINION:
                sequence.push_back(std::make_tuple(MINION, false, std::get<unsigned>(*(++arg))));
                break;
            }
        }
    }
    return sequence;
}
