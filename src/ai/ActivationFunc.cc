#include "ai/ActivationFunc.hpp"

ActivationFunc::ActivationFunc(const ActivationFuncType& type): type_(type) {}

double ActivationFunc::operator()(double input) const
{
    using enum ActivationFuncType;

    switch(type_)
    {
    case ID:
        return input;
    default:
        return 0.;
    }
}