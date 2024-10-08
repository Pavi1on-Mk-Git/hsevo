#ifndef CONNECTION_H
#define CONNECTION_H

struct Connection
{
    unsigned from, to;
    double weight;
    bool enabled;

    Connection(unsigned from, unsigned to, double weight, bool enabled = true);
};

#endif