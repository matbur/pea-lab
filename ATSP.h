#pragma once

#include <cmath>
#include <vector>
#include <set>

#include "Graph.h"
#include "Permutation.h"
#include "Heap.h"
#include <list>
#include <map>

typedef std::vector<int> veci;
typedef std::vector<veci> vveci;

struct cmpMapvv {
    bool operator()(const veci &a, const veci &b) const {
        return a.size() == b.size() ? a < b : a.size() < b.size();
    }
};

typedef std::map<veci, veci, cmpMapvv> mapvv;

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
     * Rozwiazanie problemu algorytmem Podzialu i Ograniczen.
     */
    static ATSP *BB(const Graph *graph);

    void print();

    int get_sum_weights();


    static ATSP *Dynamic(const Graph *graph);

    static vveci get_sets(int n, int r);

    static bool is_in(veci vec, int val);

    static mapvv generate_subsets(int n);

    static mapvv fill_map(Graph graph, mapvv map);

    static void print_vec(veci vec, std::string c = "\n");

    static veci get_path(mapvv map);

    static bool are_disjoint(veci outer, veci inner);


    static ATSP *Approximation(const Graph *graph);

    static void Prime(const Graph &graph, Graph &outGraph);
};
