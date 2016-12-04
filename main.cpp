#include <iostream>
#include <ctime>
#include <chrono>

#include "Menu.h"


int main() {
    srand((unsigned int) time(nullptr));

//    Menu::tspMenu();

    auto g = Graph();
    File::load("4.txt", g);
//    File::load("10/10_0.tsp", g);
    auto atsp = ATSP::Dynamic(&g);

    auto t = chrono::system_clock::now().time_since_epoch().count();
    auto map = ATSP::fill_map(g);
    auto t2 = chrono::system_clock::now().time_since_epoch().count();
    for (auto i: map) {
        ATSP::print_vec(i.first, ": ");
        ATSP::print_vec(i.second);
    }
    cout << (t2 - t) / 1000; // microseconds


    return 0;
}
