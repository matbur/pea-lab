#include <iostream>
#include <ctime>

#include "Menu.h"


int main() {
    srand((unsigned int) time(nullptr));

//    Menu::tspMenu();
    auto comb = ATSP::generate_combination(3);
    auto c1 = comb[0];
    set<int>::iterator i;
    for (auto s: c1) {
        for (i = s->begin(); i != s->end(); i++){
            cout << *i << ' ';
        }
        puts("");
    }


    return 0;
}
