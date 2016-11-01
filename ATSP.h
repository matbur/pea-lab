#pragma once

#include <cmath>
#include <vector>

#include "Graph.h"
#include "Permutation.h"

typedef std::vector<int> veci;

class ATSP {
    Permutation *permutation;
    Graph *graph;

    /**
     * Metoda redukuje wszystkie dlugosci drog
     * w rzedach i kolumnach
     */
    static int reduce(Graph *graph);

    /**
     * Metoda na podstawie grafu i rzedu zwraca
     * najbardziej obiecujacy nastepny punkt
     */
    static int find_min(Graph *graph, int row);

    /**
     * Metoda wstawia oo w calym rzedzie i kolumnie tak,
     * by te drogi nie byly pozniej uwzgledniane w szukaniu tras
     */
    static void set_infty(Graph *graph, int row, int col);

    /**
     * Metoda wypelnia nowy graf ze starego wedlug
     * danych z wektora odwiedzonych miast
     */
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
    static ATSP *BB(const Graph *graph);

    void print();

    int get_sum_weights();
};
