#pragma once

struct Edge {
    int from;
    int to;
    int weight;

    bool operator==(const Edge &e) const;

    bool operator!=(const Edge &e) const;
};
