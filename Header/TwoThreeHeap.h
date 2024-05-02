#ifndef TWOTHREEHEAP_H
#define TWOTHREEHEAP_H

#include <iostream>
#include <cmath>

template <typename T>
class Node23;

template <typename T>
int merge_nodes(Node23<T> **a, Node23<T> **b);

template <typename T>
class Node23
{
    template <typename Y>
    friend class Heap23;
    template <typename Y>
    friend int merge_nodes(Node23<Y> **a, Node23<Y> **b);

public:
    Node23(T key, T value);

    T priority() { return key_; }
    T value() { return value_; }

    void addChild(Node23<T> *node);
    void removeChild(Node23<T> *child);
    void replaceChild(Node23<T> *new_node);
    void print(std::ostream &out, unsigned level);

protected:
    void printPartners(std::ostream &out, unsigned level);

private:
    Node23 *parent;
    Node23 *child;
    Node23 *left;
    Node23 *right;
    Node23 *partner;

    bool extra;
    int dim;
    T key_;
    T value_;
};

template <typename T>
class Heap23
{
public:
    Heap23(int max_nodes = 100000000);
    ~Heap23();

    Node23<T> *insert(int key, T value);
    Node23<T> *min();
    Node23<T> *extractMin();
    bool merge(Heap23<T> &heap);
    void remove(Node23<T> *node);
    void decreaseKey(Node23<T> *node, int new_key);
    void print(std::ostream &out);
    bool isEmpty();

protected:
    void meld(Node23<T> *list);

private:
    Node23<T> **trees;
    int max_trees_;
    int nnodes;
    int value;
};

#endif
