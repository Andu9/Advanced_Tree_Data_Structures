//
// Created by Cosmin on 24.04.2024.
//

#ifndef FIBONACCIHEAP_FIBONACCIHEAP_H
#define FIBONACCIHEAP_FIBONACCIHEAP_H

#include <iostream>
#include <vector>
#include <cmath>

struct Node {
    int key;
    Node *parent{nullptr};
    Node *child{nullptr};
    Node *left{nullptr};
    Node *right{nullptr};

    bool marked{false};
    int degree{0};

    explicit Node(int k) : key(k) {}
};

class FibonacciHeap {
private:
    Node* rootNode;
    Node* minNode;
    int size;

    void mergeList(Node*);
    void consolidate();
    void heapLink(Node*, Node*);
    void removeFromList(Node*);
    void cascadingCut();
public:
    FibonacciHeap() : minNode{nullptr}, rootNode{nullptr}, size{0} {}
    void insert(int);
    void unionOperation(FibonacciHeap&);
    int extractMin();
    void decreaseKey(Node*, int);
    [[maybe_unused]] [[nodiscard]] int getMin() const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] int getSize() const;

    friend std::ostream& operator<<(std::ostream&, FibonacciHeap);
};


#endif //FIBONACCIHEAP_FIBONACCIHEAP_H
