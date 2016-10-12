#pragma once

#include <cmath>

#include "Graph.h"
#include "Permutation.h"

class ATSP {
    Permutation *permutation;
    Graph *graph;

public:
    ATSP(Permutation *p, Graph *g);

    /**
     * Rozwiazanie problemu metoda przegladu zupelnego.
     * Zawsze optymalny wynik.
     */
    static ATSP *BruteForce(const Graph *graph);

    void print();
};
