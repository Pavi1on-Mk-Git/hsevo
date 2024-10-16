#ifndef CONNECTION_H
#define CONNECTION_H

struct Connection
{
    static constexpr double MIN_WEIGHT = 0., MAX_WEIGHT = 1.;
    unsigned from, to;
    double weight;
    bool enabled;

    Connection(unsigned from, unsigned to, double weight, bool enabled = true);
};

#endif