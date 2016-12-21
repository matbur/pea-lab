#include "EdgeList.h"

/**
    EDGE NODE
*/
EdgeList::EdgeNode::EdgeNode()
        : edge(nullptr), prev(nullptr), next(nullptr) { }


/**
    EDGE LIST
*/

EdgeList::EdgeList()
        : head(nullptr), tail(nullptr), length(0) { }

EdgeList::EdgeList(const EdgeList &nb)
        : head(nullptr), tail(nullptr), length(0) {
    if (this == &nb)
        return;

    length = nb.length;

    EdgeNode *node = nb.head;
    while (node) {
        append(*node->edge);
        node = node->next;
    }
}

EdgeList::~EdgeList() {
    clear();
}

void EdgeList::clear() {
    while (head) {
        EdgeNode *old_head = head;
        head = head->next;
        delete old_head->edge;
        delete old_head;
    }

    head = nullptr;
    tail = nullptr;
    length = 0;
}

EdgeList &EdgeList::operator=(const EdgeList &list) {
    if (this == &list)
        return *this;

    clear();
    length = list.length;

    EdgeNode *node = list.head;
    while (node) {
        append(*node->edge);
        node = node->next;
    }

    return *this;
}

int EdgeList::getSize() const {
    return length;
}

void EdgeList::append(const Edge &edge) {
    append(edge.from, edge.to, edge.weight);
}

void EdgeList::append(int from, int to, int weight) {
    Edge *edge = new Edge;
    edge->from = from;
    edge->to = to;
    edge->weight = weight;

    EdgeNode *node = new EdgeNode();
    node->edge = edge;

    if (!head) {
        head = node;
        tail = node;
        return;
    }

    node->prev = tail;
    tail->next = node;

    tail = node;

    length++;
}

void EdgeList::appendUnique(const EdgeList &list) {
    for (auto e : list) {
        if (find(e.from, e.to) == -1)
            append(e);
    }
}

bool EdgeList::isFirst(const Edge &e) const {
    return head
           && head->edge
           && *head->edge == e;
}

int EdgeList::find(int from, int to) const {
    EdgeNode *node = head;
    Edge *edge;
    while (node) {
        edge = node->edge;
        if (edge->from == from && edge->to == to)
            return edge->weight;

        node = node->next;
    }

    return -1;
}

EdgeList::Iterator EdgeList::begin() const {
    return Iterator(head);
}

EdgeList::Iterator EdgeList::end() const {
    return Iterator(nullptr);
}

EdgeList::Iterator EdgeList::getBeginIterator() const {
    return Iterator(head);
}

EdgeList::Iterator EdgeList::getEndIterator() const {
    return Iterator(tail);
}


/**
    ITERATOR
*/

EdgeList::Iterator::Iterator(EdgeNode *startNode)
        : node(startNode), startNode(startNode) { }

EdgeList::Iterator::Iterator()
        : node(nullptr), startNode(nullptr) { }

bool EdgeList::Iterator::operator!=(const EdgeList::Iterator &it) const {
    return node != it.node;
}

EdgeList::Iterator &EdgeList::Iterator::operator++() {
    if (node)
        node = node->next;

    return *this;
}

EdgeList::Iterator &EdgeList::Iterator::operator--() {
    if (node)
        node = node->prev;

    return *this;
}

Edge EdgeList::Iterator::operator*() {
    Edge e = {-1, -1, -1};

    if (node && node->edge) {
        e.from = node->edge->from;
        e.to = node->edge->to;
        e.weight = node->edge->weight;
    }

    return e;
}

bool EdgeList::Iterator::done() {
    return !node;
}

void EdgeList::Iterator::rewind() {
    node = startNode;
}

bool EdgeList::Iterator::first() {
    return node == startNode;
}

int EdgeList::getWeightsSum() const {
    int sum = 0;
    for (auto e : *this)
        sum += e.weight;

    return sum;
}


// example usage

/*
int main() {
    EdgeList::Iterator it;
    EdgeList list;
    list.append(0, 1, 5);
    list.append(0, 2, 3);
    list.append(1, 2, 1);
    list.append(1, 3, 6);
    list.append(2, 3, 10);


    printf("print list1 forwards\n");
    for(auto e : list) {
        printf("%d->%d: %d\n", e.from, e.to, e.weight);
    }

    printf("print list1 backwards\n");
    it = list.getEndIterator();
    for(; !it.done(); --it) {
        Edge e = *it;
        printf("%d->%d: %d\n", e.from, e.to, e.weight);
    }

    printf("rewind iterator\n");
    it.rewind();
    
    printf("print list1 backwards using the same iterator\n");
    for(; !it.done(); --it) {
        Edge e = *it;
        printf("%d->%d: %d\n", e.from, e.to, e.weight);
    }

    printf("copy list1 to list2\n");
    EdgeList l2 = list;

    printf("print list2 forwards\n");
    for(auto e : l2) {
        printf("%d->%d: %d\n", e.from, e.to, e.weight);
    }

    printf("append values on list1\n");
    list.append(4, 2, 4);
    list.append(5, 4, 7);


    printf("print list1 forwards\n");
    for(auto e : list) {
        printf("%d->%d: %d\n", e.from, e.to, e.weight);
    }

    printf("print list2 forwards\n");
    for(auto e : l2) {
        printf("%d->%d: %d\n", e.from, e.to, e.weight);
    }



    return 0;
}

*/