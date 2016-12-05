#include "Permutation.h"

Permutation::Permutation(int length) : length(length), tab(new int[length]) {
    for (auto i = 0; i < length; i++)
        tab[i] = i;
}

Permutation::Permutation(int n, int *tab) : length(n), tab(tab) {}

Permutation::~Permutation() {
    delete[] tab;
    tab = nullptr;
    length = 0;
}

Permutation &Permutation::operator=(const Permutation &p) {
    length = p.length;
    delete tab;
    tab = new int[length];
    for (auto i = 0; i < length; i++) {
        tab[i] = p.tab[i];
    }
    return *this;
}

bool Permutation::next() {
    if (length == 1)                                            // tablica 1-elementowa nie ma innej permutacji
        return false;

    auto index = length;
    while (--index && tab[index] < tab[index - 1]);             // sprawdza ile elementow jest ustawiona malejaco

    if (!index)                                                 // jesli wszystkie el. ulozone malejaco, to koniec
        return false;

    auto max = index--;
    for (auto i = index + 2; i < length; i++)
        if (tab[index] < tab[i])
            max = i;

    swap(index, max);

    max = length;
    while (++index < --max)
        swap(index, max);

    return true;
}

int Permutation::operator[](int index) {
    return tab[index];
}

void Permutation::swap(int a, int b) {
    auto temp = tab[a];
    tab[a] = tab[b];
    tab[b] = temp;
}

void Permutation::print() {
    do {
        for (auto i = 0; i < length; i++)
            printf("%d ", tab[i]);
        printf("\n");
    } while (next());
}

void Permutation::printTab() {
    printf("<");
    auto i = 0;
    for (; i < length - 1; i++)
        printf("%d, ", tab[i]);

    printf("%d>\n", tab[i]);
}

Permutation::Permutation(std::vector<int> vec)
        : length((int) vec.size()), tab(new int[length]) {
    for (auto i = 0; i < length; i++) {
        tab[i] = vec[i];
    }
}



