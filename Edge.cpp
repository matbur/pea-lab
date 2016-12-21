#include "Edge.h"

bool Edge::operator==(const Edge &e) const {
    return from == e.from
           && to == e.to
           && weight == e.weight;
}

bool Edge::operator!=(const Edge &e) const {
    return from != e.from
           || to != e.to
           || weight != e.weight;
}
