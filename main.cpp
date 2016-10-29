#include <iostream>
#include <ctime>

#include "Menu.h"


void testBB() {
    string name = "10.txt";
    Graph *data = new Graph();
    File::load(name, *data);
    data->print();
    ATSP::BruteForce(data)->print();
    ATSP::BB(data)->print();
}

int main() {
    srand((unsigned int) time(nullptr));

    Menu::tspMenu();
//    testBB();

//    auto g = new Graph(4);
//    cout << g->toString() ;

    return 0;
}
