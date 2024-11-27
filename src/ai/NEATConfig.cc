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
    concat(interspecies_mating_prob);
    concat(inherit_connection_disabled_prob);

    return name_stream.str();
}
