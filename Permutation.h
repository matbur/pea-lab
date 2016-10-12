//
// Created on 22.05.16.
//

#pragma once

#include "iostream"


class Permutation {
public:
    int length, *tab;

    void swap(int a, int b);

    Permutation(int length);

    Permutation(int n, int *tab);

    ~Permutation();

    Permutation &operator=(const Permutation &p);

    int operator[](int index);

    /**
     * Metoda ustawia nastepna permutacje w tablicy tab.
     * Zwraca true jesli to jeszcze elementy nie sa ustawione malejaco i false w.p.p.
     */
    bool next();

    void print();

    void printTab();
};