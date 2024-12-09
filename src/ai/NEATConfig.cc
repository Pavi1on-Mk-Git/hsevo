#include "ai/NEATConfig.h"

#include <algorithm>
#include <sstream>

std::string NEATConfig::name() const
{
    std::stringstream name_stream;

    auto concat = [&name_stream](const auto& value) { name_stream << value << '_'; };

    concat(population_size);
    concat(iterations);
    concat(activation.name());
    concat(similarity_threshold);
    concat(excess_coeff);
    concat(disjoint_coeff);
    concat(weight_coeff);
    concat(weight_mutation_prob);
    concat(add_node_mutation_prob);
    concat(add_connection_prob);
    concat(weight_perturbation_prob);
    concat(mutation_strength);
    concat(crossover_prob);
    concat(inherit_connection_disabled_prob);

    return name_stream.str();
}

NEATConfig default_config()
{
    return NEATConfig{
        .population_size = 20,
        .iterations = 1000,
        .activation = ActivationFuncType::ID,
        .similarity_threshold = 4.,
        .excess_coeff = 1.,
        .disjoint_coeff = 1.,
        .weight_coeff = 3.,
        .weight_mutation_prob = 0.8,
        .add_node_mutation_prob = 0.02,
        .add_connection_prob = 0.05,
        .weight_perturbation_prob = 0.9,
        .mutation_strength = 0.2,
        .crossover_prob = 0.75,
        .inherit_connection_disabled_prob = 0.75,
    };
}
