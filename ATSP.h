#pragma once

#include <cmath>
#include <vector>

#include "Graph.h"
#include "Permutation.h"

typedef std::vector<int> veci;

class ATSP {
    Permutation *permutation;
    Graph *graph;

    static int reduce(Graph *graph);

    static int find_min(Graph *graph, int row);

    static void set_infty(Graph *graph, int row, int col);

    static void new_graph(const Graph *old_graph, Graph *graph, veci v);

public:
    ATSP(Permutation *p, Graph *g);

    /**
     * Rozwiazanie problemu metoda przegladu zupelnego.
     * Zawsze optymalny wynik.
     */
    static ATSP *BruteForce(const Graph *graph);

    /**
     * Rozwiazanie problemu algorytmem zachlannym.
     * Szybkie, ale nie ma gwarancji na optymalny wynik.
     */
    static ATSP *Greedy(const Graph *graph, int start = 0);

    /**
     * Rozwiazanie problemu algorytmem Podzialu i Ograniczen.
     */
    static ATSP *BB(const Graph *g);

    void print();
};
