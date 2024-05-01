//
// Created by Cosmin on 24.04.2024.
//

#ifndef FIBONACCIHEAP_FIBONACCIHEAP_H
#define FIBONACCIHEAP_FIBONACCIHEAP_H

#include <iostream>
#include <vector>
#include <cmath>

template<typename T>
struct Node {
    T key;
    Node *parent{nullptr};
    Node *child{nullptr};
    Node *left{nullptr};
    Node *right{nullptr};

    bool marked{false};
    int degree{0};

    explicit Node(T k) : key(k) {}
};

template<typename T>
class FibonacciHeap {
private:
    Node<T>* rootNode;
    Node<T>* minNode;
    int size;

    void consolidate();
    void heapLink(Node<T>*, Node<T>*);
    void mergeWithRootList(Node<T>*);
    void removeFromRootList(Node<T>*);
    static void mergeWithChildList(Node<T>*, Node<T>*);
    static void removeFromChildList(Node<T>*, Node<T>*);
    void cut(Node<T>*, Node<T>*);
    void cascadingCut(Node<T>*);
public:
    FibonacciHeap() : minNode{nullptr}, rootNode{nullptr}, size{0} {}
    void insert(T);

    [[maybe_unused]] void unionOperation(FibonacciHeap&);
    T extractMin();

    [[maybe_unused]] void decreaseKey(Node<T>*, int);

    [[maybe_unused]] T deleteNode(Node<T>*);
    [[maybe_unused]] [[nodiscard]] T getMin() const;

    [[maybe_unused]] [[nodiscard]] bool isEmpty() const;

    [[maybe_unused]] [[nodiscard]] int getSize() const;

    friend std::ostream& operator<<(std::ostream&, FibonacciHeap);
};


#endif //FIBONACCIHEAP_FIBONACCIHEAP_H
