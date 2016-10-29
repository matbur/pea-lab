#include <algorithm>
#include "ATSP.h"

using namespace std;


ATSP::ATSP(Permutation *p, Graph *g) : permutation(p), graph(g) {}

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

ATSP *ATSP::BB(const Graph *graph) {
    auto dim = graph->getPoints();
    veci visited;
    Graph *temp_graph;
    auto best_graph = new Graph(*graph);
    auto best_permutation = new Permutation(dim);
    auto tab = new int[dim];

    for (auto row = 0; row < dim; row++) {
        visited.clear();
        visited.push_back(row);

        temp_graph = new Graph(*graph);

        reduce(temp_graph);

        for (auto i = 0; i < dim; i++) {
            temp_graph->setWeight(i, row, -1);
        }

        int col, r;
        for (auto i = 1; i < dim; i++) {
            r = visited.back();
            col = find_min(temp_graph, r);
            visited.push_back(col);

            set_infty(temp_graph, r, col);
        }

        while (visited.front() != 0) {
            auto begin = visited.begin();
            rotate(begin, begin + 1, visited.end());
        }

        new_graph(graph, temp_graph, visited);

        copy(visited.begin(), visited.end(), tab);
        auto p = new Permutation(dim, tab);


        if (*temp_graph < *best_graph) {
            *best_graph = *temp_graph;
            *best_permutation = *p;
        }
    }

    return new ATSP(best_permutation, best_graph);
}

int ATSP::reduce(Graph *graph) {
    int dim = graph->getPoints();
    int lb = 0;
    int min;
    int temp;

    for (auto row = 0; row < dim; row++) {
        min = INT_MAX;
        for (auto col = 0; col < dim; col++) {
            temp = graph->getWeight(row, col);
            if (temp < min and temp >= 0)
                min = temp;
        }
        for (auto col = 0; col < dim; col++) {
            temp = graph->getWeight(row, col);
            if (temp > 0)
                graph->setWeight(row, col, temp - min);
        }
        if (min < INT_MAX) {
            lb += min;
        }
    }
    for (auto col = 0; col < dim; col++) {
        min = INT_MAX;
        for (auto row = 0; row < dim; row++) {
            temp = graph->getWeight(row, col);
            if (temp < min and temp >= 0)
                min = temp;
        }
        for (auto row = 0; row < dim; row++) {
            temp = graph->getWeight(row, col);
            if (temp > 0)
                graph->setWeight(row, col, temp - min);
        }
        if (min < INT_MAX) {
            lb += min;
        }
    }

    return lb;
}

int ATSP::find_min(Graph *graph, int row) {
    auto dim = graph->getPoints();
    Graph *temp_graph;
    veci min_row((unsigned long) dim);
    int temp;

    for (auto col = 0; col < dim; col++) {
        temp_graph = new Graph(*graph);
        temp = temp_graph->getWeight(row, col);
        if (temp == -1) {
            min_row[col] = INT_MAX;
            continue;
        }
        set_infty(temp_graph, row, col);
        temp += reduce(temp_graph);

        min_row[col] = temp;
    }

    auto begin = min_row.begin();
    auto last = min_row.end();
    auto min = *min_element(begin, last);           // Znajdz najmniejszy element
    return find(begin, last, min) - begin;          // i zwroc jego index
}

void ATSP::set_infty(Graph *graph, int row, int col) {
    auto dim = graph->getPoints();
    graph->setWeight(col, row, -1);
    for (auto i = 0; i < dim; i++) {
        graph->setWeight(i, col, -1);
        graph->setWeight(row, i, -1);
    }
}

void ATSP::new_graph(const Graph *old_graph, Graph *graph, veci v) {
    auto row = v.back();
    auto col = v.front();
    graph->setWeight(row, col, old_graph->getWeight(row, col));
    auto dim = old_graph->getPoints();
    for (auto i = 1; i < dim; i++) {
        row = v[i - 1];
        col = v[i];
        graph->setWeight(row, col, old_graph->getWeight(row, col));
    }
}

