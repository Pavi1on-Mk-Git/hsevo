#include "RandomPlayerLogic.h"

RandomPlayerLogic::RandomPlayerLogic(const DeckList& decklist, std::ranlux24_base& random_engine):
    PlayerLogic(decklist), random_engine(random_engine)
{}

std::unique_ptr<Action> RandomPlayerLogic::choose_action(const Game& game, std::vector<std::unique_ptr<Action>> actions)
    const
{
    static_cast<void>(game);
    return std::move(actions.at(random_engine() % actions.size()));
}