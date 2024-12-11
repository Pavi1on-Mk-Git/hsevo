#include <fstream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include "ai/NEAT.h"
#include "ai/SimpleEvo.hpp"
#include "ai/evo_functions.hpp"
#include "logic/decklists.h"
#include "logic/run_game.h"
#include "players/EvoPlayerLogic.hpp"
#include "utils/Rng.h"

int main()
{
    spdlog::set_default_logger(spdlog::basic_logger_mt("file_logger", "logs/hsevo.log", true));
    spdlog::set_pattern("[%l] %v");
    spdlog::set_level(spdlog::level::off);

    unsigned seed = 12;
    std::array<NEATConfig, DECK_COUNT> configs{default_config(), default_config(), default_config()};
    const unsigned ITERATIONS = 500;
    const std::array<Decklist, DECK_COUNT> decklists = get_decklists();

    Rng rng(seed);

    std::vector<NEAT> populations;
    std::ranges::transform(configs, std::back_inserter(populations), [&](const NEATConfig& config) {
        return NEAT(config, rng);
    });

    std::array<std::vector<Network>, DECK_COUNT> hall_of_champions;
    std::array<unsigned, DECK_COUNT> champion_scores;
    std::array<std::vector<unsigned>, DECK_COUNT> score_history;
    for(auto [score_vec, config]: std::views::zip(score_history, configs))
        score_vec.reserve(ITERATIONS);

    for(unsigned iteration = 0; iteration < ITERATIONS; ++iteration)
    {
        std::array<std::vector<Network>, DECK_COUNT> iteration_networks;
        std::ranges::transform(populations, iteration_networks.begin(), [](const NEAT& neat) {
            return neat.networks();
        });
        std::array<std::optional<std::pair<Network, unsigned>>, DECK_COUNT> iteration_bests;

        auto iteration_scores = score_populations<Network, DECK_COUNT>(iteration_networks, decklists, rng);

        for(auto [best, population, new_scores, champions, decklist, champion_score, score_vec]: std::views::zip(
                iteration_bests, populations, iteration_scores, hall_of_champions, decklists, champion_scores,
                score_history
            ))
        {
            best = population.assign_scores(new_scores);

            auto contender_score = score_hall_of_champions(champions, best->first, decklist, rng);

            if(contender_score > champions.size() / 2)
            {
                champions.push_back(best->first);
                champion_score = best->second;
            }

            score_vec.push_back(champion_score);
            population.epoch();
        }
    }
}
