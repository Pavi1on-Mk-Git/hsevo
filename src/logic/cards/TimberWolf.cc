#include "logic/cards/TimberWolf.h"

#include "logic/Game.h"

const unsigned TIMBER_WOLF_BUFF_AMOUNT = 1;

void TimberWolf::on_minion_summon(Game&, Minion& minion, unsigned id, unsigned) const
{
    if(minion.tribe == Tribe::BEAST)
    {
        minion.attack += TIMBER_WOLF_BUFF_AMOUNT;
        minion.auras_applied.push_back(id);
    }
}

void TimberWolf::on_summon(Game& game, unsigned position_played) const
{
    auto& board = game.current_player().board;

    for(unsigned minion_position = 0; minion_position < board.minion_count(); ++minion_position)
    {
        auto& minion = board.get_minion(minion_position);

        if(minion.tribe == Tribe::BEAST)
        {
            minion.attack += TIMBER_WOLF_BUFF_AMOUNT;
            minion.auras_applied.push_back(board.get_minion(position_played).id);
        }
    }
}

void TimberWolf::on_remove(Game& game, unsigned id, unsigned player_id) const
{
    for(auto& minion: game.players.at(player_id).board)
    {
        auto found_aura = std::ranges::find(minion.auras_applied, id);
        if(found_aura != minion.auras_applied.end())
        {
            minion.attack -= TIMBER_WOLF_BUFF_AMOUNT;
            std::erase(minion.auras_applied, id);
        }
    }
}
