#include <iostream>
#include <ctime>
#include <chrono>

#include "Menu.h"


int main() {
    srand((unsigned int) time(nullptr));

    Menu::tspMenu();

//    auto g = Graph();
//    File::load("5/5_27.tsp", g);
//    File::load("4.txt", g);
//    File::load("6/6_0.tsp", g);
//    File::load("8/8_0.tsp", g);
//    File::load("9/9_0.tsp", g);
//    File::load("10/10_0.tsp", g);
//    File::load("11/11_0.tsp", g);
//    File::load("12/12_0.tsp", g);
//
//    g.print();
//    puts("dyn");
//    ATSP::Dynamic(&g)->print();
//    puts("brute");
//    ATSP::BruteForce(&g)->print();

    return 0;
}
