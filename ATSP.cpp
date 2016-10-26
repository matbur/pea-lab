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

ATSP *ATSP::Greedy(const Graph *graph, int start /*= 0*/) {
    auto n = graph->getPoints();                                            // ilosc miast do odwiedzenia

    if (start >= n)                                                         // wiercholek starowy musi istniec
        return nullptr;

    auto minGraph = new Graph(n);                                           // graf z najkrotsza droga
    int *permTab = new int[n];                                              // permutacja z najkrotsza droga

    auto visited = new bool[n]{false};                                      // tablica odwiedzonych

    int min, temp, current = start, next = start;
    for (auto i = 0; i < n; i++) {
        visited[current] = true;                                            // oznacz jako odwiedzone
        permTab[i] = current;                                               // ustawienie elementu w permutacji
        min = INT_MAX;                                                      // zeby potem zmniejszyc
        for (auto col = 0; col < n; col++) {
            temp = graph->getWeight(current, col);
            if (temp != -1 and temp < min and !visited[col]) {              // jesli jeszcze wierzcholek nie odwiedzony
                min = temp;                                                 // wartosc minimalnej krawedzi
                next = col;                                                 // indeks minimalnej krawedzi
            }
        }
        minGraph->addEdge(current, next, min, true);                        // dodanie krawedzi do grafu koncowego
        current = next;                                                     // ustawienie nastepnego elementu
    }
    minGraph->addEdge(current, start, graph->getWeight(current, start), true);   // dodanie ostatniej krawedzi

    delete[] visited;
    return new ATSP(new Permutation(n, permTab), minGraph);
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
