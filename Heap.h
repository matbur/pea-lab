//
// Created by matbur on 28.02.16.
//

#pragma once

#include <iostream>
#include <cmath>
#include "Edge.h"

enum HeapType_t {
    HEAP_MIN,
    HEAP_MAX
};

class Heap {
    Edge *tab;
    int length;
    HeapType_t type;

    /**
     * Funkcja zwraca indeks rodzica
     */
    int get_parent(int key);

    /**
     * Funkcja zwraca indeks lewego dziecka
     */
    int get_left(int key);

    /**
     * Funkcja zwraca indeks prawego dziecka
     */
    int get_right(int key);

    /**
     * Funkcja zamienia elementy a i b w tablicy
     */
    void swap(int a, int b);

    /**
     * Funkcja porownuje elementy a i b w tablicy
     * Porównanie zależy od typu kopca.
     */
    bool compare(int a, int b);

    /**
     * Funkcja zmienia rozmiar kopca
     */
    void realloc(int new_length);

public:
    Heap(HeapType_t htype = HEAP_MIN);

    /**
     * Konstruktor tworzy kopiec z tablicy itab
     */
    Heap(Edge *itab, int size, HeapType_t htype = HEAP_MIN);

    ~Heap();

    /**
     * Funkcja pcha element na kopiec
     */
    void push(Edge edge);

    /**
     * Funkcja usuwa i zwraca korzen kopca
     */
    Edge pop();

    /**
     * Funkcja czysci kopiec
     */
    void clear();

    /**
     * Funkcja tworzy losowy stos o dlugosci n
     */
    void generate_random(int n);

    /**
     * Funkcja sprawdza czy kopiec jest pusty
     */
    bool is_empty();

    int get_length();

    void print();

    int countRows();

    Edge operator[](int n);

    friend std::ostream &operator<<(std::ostream &, Heap &);
};
