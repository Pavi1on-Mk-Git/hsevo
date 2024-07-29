#include "players/RandomPlayerLogic.h"

#include "utils/Rng.h"

RandomPlayerLogic::RandomPlayerLogic(const DeckList& decklist): PlayerLogic(decklist) {}

std::unique_ptr<Action> RandomPlayerLogic::choose_action(const Game& game, std::vector<std::unique_ptr<Action>> actions)
    const
{
    static_cast<void>(game);
    return std::move(actions.at(Rng::instance()->uniform_int(0, actions.size())));
}