//
// Created on 20.05.16.
//

#include "ATSP.h"

ATSP::ATSP(Permutation *p, Graph *g) : permutation(p), graph(g) { }

ATSP *ATSP::BruteForce(const Graph *graph) {
    auto n = graph->getPoints();                                            // ilosc miast do odwiedzenia

    Graph *tempGraph;                                                       // tymczasowy graf
    auto *minGraph = new Graph(n);                                          // graf z najkrotsza droga

    auto permutation = new Permutation(n);                                  // permutacja do iteracji
    auto minPerm = new Permutation(n);                                      // permutacja z najkrotsza droga

    do {
        tempGraph = new Graph(n);                                           // nowy, pusty graf
        for (auto i = 0; i < n; i++) {                                      // przepisanie krawedzi wg. permutacji
            auto from = (*permutation)[i];
            auto to = (*permutation)[(i + 1) % n];                          // nastepny element permutacji
            auto weight = graph->getWeight(from, to);
            tempGraph->addEdge(from, to, weight, true);                     // dodanie elementu
        }

        if (*tempGraph < *minGraph) {                                       // jesli nowa droga krotsza od starej
            *minGraph = *tempGraph;                                         // nadpisanie grafu koncowego
            *minPerm = *permutation;                                        // nadpisanie permutacji koncowej
        }
        delete tempGraph;
    } while (permutation->next());                                          // nastepna permutacja

    delete permutation;
    return new ATSP(minPerm, minGraph);
}

void ATSP::print() {
    if (!this) {
        printf("brak grafu\n");
        return;
    }

    printf("\nRowiazanie: %d\n", graph->getWeightsSum());
    printf("Permutacja wierzcholkow: ");
    permutation->printTab();
    printf("\n");
    graph->print();

}
