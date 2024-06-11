#include "RandomPlayerLogic.h"

RandomPlayerLogic::RandomPlayerLogic(const DeckList& decklist, std::ranlux24_base& random_engine):
    random_engine(random_engine), decklist(decklist)
{}

std::unique_ptr<Action> RandomPlayerLogic::choose_action(std::vector<std::unique_ptr<Action>> actions) const
{
    return std::move(actions.at(random_engine() % actions.size()));
}