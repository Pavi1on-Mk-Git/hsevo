#ifndef ACTIVATION_FUNC_HPP
#define ACTIVATION_FUNC_HPP

#include <boost/serialization/access.hpp>
#include <functional>
#include <string>

/**
 * Possible types of activation functions
 */
enum class ActivationFuncType
{
    ID,
    SIGMOID,
    TANH,
    EXP,
};

/**
 * Represents an activation function of a given type
 */
class ActivationFunc
{
private:
    friend class boost::serialization::access;

    /**
     * Serialize the function into a boost archive
     *
     * @param archive Archive to serialize the function into
     * @param version Unused
     */
    template <typename Archive>
    void serialize(Archive& archive, const unsigned)
    {
        archive & type_;
    }

    /**
     * Type of the activation function
     */
    ActivationFuncType type_;
public:
    /**
     * Construct an ActivationFunc of the provided type
     *
     * @param type Type of the function. Defaults to ID
     */
    ActivationFunc(const ActivationFuncType& type = ActivationFuncType::ID);

    /**
     * Compute the value of the function using provided input
     *
     * @param input Input to the function
     */
    double operator()(double input) const;

    /**
     * Return human-readable name of the function
     *
     * @return Name of the function
     */
    std::string name() const;
};
#endif

/**
 * Output the function name into a stream
 *
 * @param out Stream to write the name to
 * @param func Instance of an activation function
 * @return Modified stream
 */
std::ostream& operator<<(std::ostream& out, const ActivationFunc& func);
