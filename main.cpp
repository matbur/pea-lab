#include <iostream>
#include <ctime>
#include <chrono>

#include "Menu.h"


int main(int argc, char **argv) {
    srand((unsigned int) time(nullptr));

//    Menu::tspMenu();

    auto g = Graph();
//    File::load(argv[1], g);
    g.generate_euclidean(10);

    g.print();
    printf("dynamic");
    ATSP::Dynamic(&g)->print();
    printf("approx");
    ATSP::Approximation(&g)->print();

    return 0;
}
