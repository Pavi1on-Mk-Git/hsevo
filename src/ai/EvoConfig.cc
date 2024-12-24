#include "ai/EvoConfig.h"

#include <sstream>

std::string EvoConfig::name() const
{
    std::stringstream name_stream;

    auto concat = [&name_stream](const auto& value) { name_stream << value << '_'; };

    concat(mu);
    concat(lambda);
    concat(init_mutation_strength);

    return name_stream.str();
}

EvoConfig EvoConfig::default_config()
{
    return EvoConfig{
        .mu = 100,
        .lambda = 500,
        .init_mutation_strength = 0.2,
    };
}
