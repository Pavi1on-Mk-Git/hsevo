#ifndef ACTIVATION_FUNC_HPP
#define ACTIVATION_FUNC_HPP

#include <boost/serialization/access.hpp>
#include <functional>

enum class ActivationFuncType
{
    ID,
};

class ActivationFunc
{
private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive& archive, const unsigned)
    {
        archive & type_;
    }

    ActivationFuncType type_;
public:
    ActivationFunc(const ActivationFuncType& type = ActivationFuncType::ID);
    double operator()(double input) const;
};

#endif
