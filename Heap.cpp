//
// Created by matbur on 28.02.16.
//

#include "Heap.h"

Heap::Heap(HeapType_t htype/* = HEAP_MIN*/)
        : tab(nullptr), length(0), type(htype) { }

Heap::Heap(Edge *itab, int size, HeapType_t htype/* = HEAP_MIN*/)
        : tab(nullptr), length(0), type(htype) {
    if (!itab) return;

    for (int i = 0; i < size; i++)
        push(itab[i]);
}

Heap::~Heap() {
    clear();
}

void Heap::clear() {
    delete[] tab;
    tab = nullptr;
    length = 0;
}

bool Heap::compare(int a, int b) {
    if (type == HEAP_MIN)
        return tab[a].weight < tab[b].weight;

    return tab[a].weight > tab[b].weight;
}

void Heap::realloc(int new_length) {
    Edge *new_tab = new Edge[new_length];

    int min = std::min(new_length, length);
    for (int i = 0; i < min; i++)
        new_tab[i] = tab[i];

    if (tab)
        delete[] tab;

    tab = new_tab;
    length = new_length;
}

void Heap::push(Edge edge) {
    realloc(length + 1);

    int key = length - 1;
    int parent;
    bool changed = true;

    tab[key] = edge;                           // ustawienie nowej wartości
    while (changed) {                           // przenoszenie elementu w strone korzenia
        parent = get_parent(key);
        changed = compare(key, parent);

        if (changed) {
            swap(key, parent);
            key = parent;
        }
    }
}

Edge Heap::pop() {
    if (!length)
        return {-1, -1, -1};

    else if (length == 1) {
        Edge n = tab[0];
        clear();

        return n;
    }

    Edge old_root = tab[0];                  // wartosc do zwrocenia
    swap(0, length - 1);

    realloc(length - 1);

    int key = 0;
    int child, left, right;
    bool changed = true;

    while (changed) {                       // przenoszenie elemntu w strone liscia
        child = key;
        left = get_left(key);
        right = get_right(key);

        if (left < length)
            child = left;

        if (right < length && compare(right, left))
            child = right;

        changed = compare(child, key);
        if (changed) {
            swap(key, child);
            key = child;
        }
    }

    return old_root;
}

int Heap::get_parent(int key) {
    return (key - 1) / 2;
}

int Heap::get_left(int key) {
    return 2 * key + 1;
}

int Heap::get_right(int key) {
    return 2 * key + 2;
}

void Heap::swap(int a, int b) {
    std::swap(tab[a], tab[b]);
}

std::ostream &operator<<(std::ostream &ostream, Heap &heap) {
    ostream << '[';
    Edge *current = heap.tab;

    if (current == nullptr) {
        ostream << ']';
        return ostream;
    }

    for (int i = 1; i < heap.length; i++) {
        ostream << current->weight << ", ";
        current++;
    }

    ostream << current->weight << ']';
    return ostream;
}

void Heap::generate_random(int n) {
    for (int i = 0; i < n; i++) {
        push(Edge());
    }
}

void Heap::print() {
    static int ntab[10] = {0};
    for (int i = 0; i < 10; i++)
        ntab[i] = (int) (pow(2, i) - 1);

    int rows = countRows();
    if (rows == 0) return;

    int row = 1;
    int left = 1;
    int last_len = 0;
    int start = ntab[rows - row];
    printf("%*s", start * 3, " ");
    for (int i = 0; i < length; i++) {
        printf("%3d", tab[i].weight);
        left--;

        if (left == 0) {
            last_len = start;

            left = std::pow(2, row);
            row++;
            start = ntab[rows - row];
            if (start)
                printf("\n%*s", start * 3, " ");
            else
                putchar('\n');
        }
        else
            printf("%*s", last_len * 3, " ");
    }

    printf("\n");
}

int Heap::countRows() {
    if (!tab || !length)
        return 0;

    return (int) std::floor(std::log2(length)) + 1;
}

bool Heap::is_empty() {
    return tab == nullptr;
}

int Heap::get_length() {
    return length;
}

Edge Heap::operator[](int n) {
    return tab[n];
}







