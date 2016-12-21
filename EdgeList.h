#pragma once

#include "Edge.h"

class EdgeList {
private:
    class EdgeNode {
    public:
        Edge *edge;
        EdgeNode *prev, *next;

        EdgeNode();
    };

public:
    class Iterator {
        EdgeNode *node;
        EdgeNode *startNode;

        Iterator(EdgeNode *startNode);

    public:
        Iterator();

        bool operator!=(const EdgeList::Iterator &it) const;

        Iterator &operator++();

        Iterator &operator--();

        Edge operator*();

        bool done();

        void rewind();

        bool first();

        friend class EdgeList;
    };


private:
    EdgeNode *head;
    EdgeNode *tail;
    int length;

    void clear();

public:
    EdgeList();

    EdgeList(const EdgeList &nb);

    ~EdgeList();

    EdgeList &operator=(const EdgeList &list);

    void append(int from, int to, int weight);

    void append(const Edge &edge);

    void appendUnique(const EdgeList &list);

    Iterator begin() const;

    Iterator end() const;

    Iterator getBeginIterator() const;

    Iterator getEndIterator() const;

    bool isFirst(const Edge &e) const;

    int getSize() const;

    int getWeightsSum() const;

    int find(int from, int to) const;
};
