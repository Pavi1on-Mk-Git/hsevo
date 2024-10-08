#include "ai/Connection.h"

Connection::Connection(unsigned from, unsigned to, double weight, bool enabled):
    from(from), to(to), weight(weight), enabled(enabled)
{}