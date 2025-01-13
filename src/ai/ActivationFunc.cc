#include "ai/ActivationFunc.hpp"

#include <cmath>

ActivationFunc::ActivationFunc(const ActivationFuncType& type): type_(type) {}

double ActivationFunc::operator()(double input) const
{
    using enum ActivationFuncType;

    switch(type_)
    {
    case ID:
        return input;
    case SIGMOID:
        return 1. / (1 + std::exp(-input));
    case TANH:
        return std::tanh(input);
    case EXP:
        return std::expm1(input);
    default:
        return 0.;
    }
}

std::string ActivationFunc::name() const
{
    using enum ActivationFuncType;

    switch(type_)
    {
    case ID:
        return "ID";
    case SIGMOID:
        return "SIGMOID";
    case TANH:
        return "TANH";
    case EXP:
        return "EXP";
    default:
        return "UNKNOWN";
    }
}

std::ostream& operator<<(std::ostream& out, const ActivationFunc& func)
{
    return out << func.name();
}
