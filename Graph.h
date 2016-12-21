#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include "EdgeList.h"

#include <vector>

class Graph {
    int points;
    int **weights;

    void clear();

    void init();

public:
    Graph();

    Graph(int points);

    Graph(const Graph &graph);

    ~Graph();

    Graph &operator=(const Graph &graph);

    bool operator<(const Graph &graph);

    bool addEdge(int from, int to, int weight, bool oneway = false);

    void reset(int points);

    void generate(int points, bool oneway = false);

    void generate_euclidean(int points);

    bool pointExists(int point) const;

    int getWeightsSum() const;

    int getPoints() const;

    int getWeight(int row, int col) const;

    void setWeight(int row, int col, int weight);

    void print() const;

    std::string toString() const;

    EdgeList getNeighbours(int from) const;

    std::vector<int> EulerCircuit();

    std::vector<int> available_vertices(int vertex);

    int last_vertex(int vertex);
};
