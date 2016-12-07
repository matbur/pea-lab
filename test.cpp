#include <iostream>
#include <ctime>
#include <chrono>

#include "Graph.h"
#include "File.h"
#include "ATSP.h"

using namespace std;

long get_time() {
    auto time = chrono::system_clock::now();
    return time.time_since_epoch().count();
}

long calc_delta(const long &start, const long &end) {
    return end - start;
}

void generate() {
    string str, path;
    Graph *graph;

    for (auto size = 4; size < 13; size++) {
        for (auto i = 0; i < 30; i++) {
            str = to_string(size);
            path = "data/" + str + "/" + str + "_" + to_string(i) + ".tsp";
            graph = new Graph();
            graph->generate(size, true);
            File::save(path, *graph);
        }
    }
}

void test() {
    string str, path;
    Graph *graph;
    ATSP *atsp;
    int s1, s2;
    long t0, t1, t2, t3;
    for (auto size = 4; size < 13; size++) {
        for (auto i = 0; i < 30; i++) {
            str = to_string(size);
            path = "data/" + str + "/" + str + "_" + to_string(i) + ".tsp";
            graph = new Graph();
            File::load(path, *graph);

            t0 = get_time();
            atsp = ATSP::Dynamic(graph);
            t1 = get_time();

            s1 = atsp->get_sum_weights();

            t2 = get_time();
            atsp = ATSP::BB(graph);
            t3 = get_time();

            s2 = atsp->get_sum_weights();

            auto t_dyn = t1 - t0;
            auto t_bb = t3 - t2;
            cout << path << " "
                 << t_dyn << " "
                 << t_bb << " "
                 << (double) t_dyn / t_bb << " "
                 << s1 << " "
                 << s2 << endl;
        }
    }
}

int main() {
    srand((unsigned int) time(nullptr));

//    generate();
    test();

    return 0;
}