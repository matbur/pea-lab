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

int ATSP::get_sum_weights() {
    return graph->getWeightsSum();
}


ATSP *ATSP::Dynamic(const Graph *graph) {
    auto n = graph->getPoints();


}

//vveci ATSP::get_sets(int dim, int r) {
//    auto v = vector<veci>();
//
//    auto indices = veci();
//    for (auto i = 0; i < r; i++) {
//        indices.push_back(i);
//    }
//
//    auto pool = veci();
//    for (auto i = 1; i < dim; i++) {
//        pool.push_back(i);
//    }
//
//    auto p = veci();
//    for (auto i: indices)
//        p.push_back(pool[i]);
//    v.push_back(p);
//
//    while (1) {
//        int i;
//        auto flag = true;
//        for (i = r - 1; i > -1; i--) {
//            if (indices[i] != i + dim - 1 - r) {
//                flag = false;
//                break;
//            }
//        }
//        if (flag)
//            return v;
//
//        indices[i] += 1;
//        for (auto j = i + 1; j < r; j++)
//            indices[j] = indices[j - 1] + 1;
//        auto p = veci();
//        for (auto i: indices)
//            p.push_back(pool[i]);
//        v.push_back(p);
//    }
//}

vveci ATSP::get_sets(int n, int r) {
    auto output = vveci();
    n--;

    std::vector<bool> selectors((unsigned long) n);
    std::fill(selectors.begin(), selectors.begin() + r, true);

    veci temp;
    do {
        temp = veci();
        for (auto i = 0; i < n; i++) {
            if (selectors[i]) {
                temp.push_back(i + 1);
            }
        }
        output.push_back(temp);
    } while (std::prev_permutation(selectors.begin(), selectors.end()));

    return output;
}

mapvv ATSP::generate_subsets(int n) {
    auto output = mapvv();

    vector<int> temp;
    for (auto i = 0; i < n; i++) {
        for (auto j: get_sets(n, i)) {
            for (auto k = 1; k < n; k++) {
                if (is_in(j, k)) {
                    continue;
                }
                temp = j;
                temp.insert(temp.begin(), k);
                output[temp] = veci(2);
            }
        }
    }

    temp = veci();
    for (auto i = 0; i < n; i++) {
        temp.push_back(i);
    }
    output[temp] = veci(2);

    return output;
}

bool ATSP::is_in(veci vec, int val) {
    for (auto i: vec) {
        if (i == val) {
            return true;
        }
    }
    return false;
}

void ATSP::print_vec(veci vec, std::string c) {
    std::cout << "(";
    for (auto i: vec) {
        std::cout << i << ", ";
    }
    std::cout << ")" << c;
}

mapvv ATSP::fill_map(Graph graph) {
    auto n = graph.getPoints();

    auto map = generate_subsets(n);

    veci set, min, temp_min, temp_sorted;
    min = veci(2);
    temp_min = veci(2);
    int city, first;

    for (auto &item: map) {
        city = item.first[0];
        if (item.first.size() == 1) {
            item.second = {graph.getWeight(0, city), 0};
            continue;
        }

        set = item.first;
        set.erase(set.begin());

        first = set[0];
        min = {map[set][0] + graph.getWeight(first, city), first};

        for (auto i = 0; i < set.size(); i++) {
            temp_sorted = set;

            std::swap(temp_sorted[0], temp_sorted[i]);
            std::sort(temp_sorted.begin() + 1, temp_sorted.end());

            first = temp_sorted[0];
            temp_sorted = {map[temp_sorted][0] + graph.getWeight(first, city), first};
            if (temp_sorted < min) {
                min = temp_sorted;
            }
        }

        item.second = min;
    }

    return map;
}
