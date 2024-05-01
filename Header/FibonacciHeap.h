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

    void consolidate();
    void heapLink(Node*, Node*);
    void mergeWithRootList(Node*);
    void removeFromRootList(Node*);
    static void mergeWithChildList(Node*, Node*);
    static void removeFromChildList(Node*, Node*);
    void cut(Node*, Node*);
    void cascadingCut(Node*);
public:
    FibonacciHeap() : minNode{nullptr}, rootNode{nullptr}, size{0} {}
    void insert(int);

    [[maybe_unused]] void unionOperation(FibonacciHeap&);
    int extractMin();

    [[maybe_unused]] void decreaseKey(Node*, int);

    [[maybe_unused]] int deleteNode(Node*);
    [[maybe_unused]] [[nodiscard]] int getMin() const;
    [[nodiscard]] bool isEmpty() const;

    [[maybe_unused]] [[nodiscard]] int getSize() const;

    friend std::ostream& operator<<(std::ostream&, FibonacciHeap);
};


#endif //FIBONACCIHEAP_FIBONACCIHEAP_H
