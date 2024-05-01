//
// Created by Cosmin on 24.04.2024.
//

#include "./Header/FibonacciHeap.h"

template<typename T>
void FibonacciHeap<T>::insert(T key) {
    auto *newNode = new Node{key};
   // Node<T> *newNode = new Node{key};
    newNode->left = newNode;
    newNode->right = newNode;

    mergeWithRootList(newNode);

    if (minNode == nullptr || newNode->key < minNode->key)
        minNode = newNode;

    size++;
}

template<typename T>
void FibonacciHeap<T>::mergeWithRootList(Node<T> *newNode) {
    if (rootNode == nullptr)
        rootNode = newNode;
    else {
        newNode->right = rootNode;
        newNode->left = rootNode->left;
        rootNode->left = newNode;
        newNode->left->right = newNode;
    }
}

template<typename T>
[[maybe_unused]] T FibonacciHeap<T>::getMin() const {
    return minNode->key;
}

template<typename T>
[[maybe_unused]] bool FibonacciHeap<T>::isEmpty() const {
    return size==0;
}

template<typename T>
[[maybe_unused]] int FibonacciHeap<T>::getSize() const {
    return size;
}

template<typename T>
[[maybe_unused]] void FibonacciHeap<T>::unionOperation(FibonacciHeap &other) {
    this->minNode = minNode->key < other.minNode->key ? minNode : other.minNode;

    Node<T> *last = other.rootNode->left;
    other.rootNode->left = rootNode->left;
    rootNode->left->right = other.rootNode;
    rootNode->left = last;
    rootNode->left->right = rootNode;

    size += other.size;
}

template<typename T>
T FibonacciHeap<T>::extractMin() {

    Node<T> *temp = minNode;

    /// copiii nodului devin arbori noi
    if (minNode->child != nullptr) {
        /// copiii nu mai au parinti :(
        Node<T> *child = minNode->child;
        do {
            child->parent = nullptr;
            child = child->right;
        } while (child != minNode->child);

        /// copiii integrati in lista (in societate)
        Node<T>* firstChild = minNode->child;
        Node<T>* lastChild = firstChild->left;
        lastChild->right = minNode;
        firstChild->left = minNode->left;
        minNode->left->right = firstChild;
        minNode->left = lastChild;
        minNode->child = nullptr;
        minNode->degree = 0;
    }

    if (minNode->right == minNode) { /// era singurul nod in toata lista
        minNode = nullptr;
        rootNode = nullptr;
    }
    else {
        minNode = minNode->right; /// temporar, clar incorect
        removeFromRootList(temp);
        consolidate(); /// aici se stabileste adevarata valoare minima noua
    }
    size--;
    return temp->key;
}

template<typename T>
void FibonacciHeap<T>::removeFromRootList(Node<T> *x) {
    if (x == nullptr)
        return;
    if (x == rootNode)
        rootNode = rootNode->right;

    /// refac legaturile acolo unde am scos nodul
    x->right->left = x->left;
    x->left->right = x->right;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, FibonacciHeap<T> FH) {
    Node<T> *it = FH.rootNode;
    do {
        os << it->key << "\n";

        it = it->right;
    } while (it != FH.rootNode);
    return os;
}

template<typename T>
void FibonacciHeap<T>::consolidate() {
    std::vector<Node<T> *> a(10, nullptr);
    Node<T> *it = rootNode;
    do {
        if (it->key < minNode->key)
            minNode = it;
        Node<T> *x = it;
        int d = x->degree;

        while (a[d] != nullptr) {
            Node<T> *y = a[d];

            if (x->key > y->key) {
                Node<T> *aux = x;
                x = y;
                y = aux;
            }

            heapLink(x, y); /// pune arborele cu radacina y ca si copil al radacinii x
            a[d] = nullptr;
            d++;

        }
        a[d] = x;

        it = x->right;
    } while (it != rootNode);

}

template<typename T>
void FibonacciHeap<T>::heapLink(Node<T> *a, Node<T> *b) {
    removeFromRootList(b); /// scoate nodul b din lista

    b->left = b->right = b;
    mergeWithChildList(a, b);
    a->degree++;
    b->parent = a;
}

template<typename T>
void FibonacciHeap<T>::mergeWithChildList(Node<T> *parent, Node<T> *newChild) {

    if (parent->child == nullptr) /// parintele nu are copii
        parent->child = newChild;
    else {
        newChild->right = parent->child->right;
        newChild->left = parent->child;
        parent->child->right->left = newChild;
        parent->child->right = newChild;
    }
}

template<typename T>
void FibonacciHeap<T>::decreaseKey(Node<T> *x, int k) {
    if (k > x->key)
        return;
    x->key = k;
    Node<T> *y = x->parent;
    if (y != nullptr && x->key < y->key) {/// proprietate de heap pierduta
        cut(y, x); /// taie legatura dintre x si y, x este pus in root list
        cascadingCut(y);
    }
    if (x->key < minNode->key)
        minNode = x;
}

template<typename T>
void FibonacciHeap<T>::cut(Node<T> *parent, Node<T> *node) {
    removeFromChildList(parent, node);
    parent->degree--;
    mergeWithRootList(node);
    node->parent = nullptr;
    node->marked = false;
}

template<typename T>
void FibonacciHeap<T>::cascadingCut(Node<T> *node) {
    Node<T> *parent = node->parent;
    if (parent != nullptr) {
        if (!node->marked)
            node->marked = true;
        else {
            cut(parent, node);
            cascadingCut(parent);
        }
    }
}

template<typename T>
void FibonacciHeap<T>::removeFromChildList(Node<T> *parent, Node<T> *node) {
    if (parent->child == parent->child->right) // exista doar un singur copil
        parent->child = nullptr;
    else if (parent->child == node) {
        parent->child = node->right;
        node->right->parent = parent;
    }
    node->left->right = node->right;
    node->right->left = node->left;
}

template<typename T>
T FibonacciHeap<T>::deleteNode(Node<T> *x) {
    decreaseKey(x, (-0x7fffffff - 1));
    return extractMin();
}

template class FibonacciHeap<int>;
template class FibonacciHeap<float>;
