#include "ai/Connection.h"

Connection::Connection(NodeId from, NodeId to, double weight, bool enabled):
    from(from), to(to), weight(weight), enabled(enabled)
{}