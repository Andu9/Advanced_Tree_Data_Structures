//
// Created by Cosmin on 24.04.2024.
//

#include "FibonacciHeap.h"

void FibonacciHeap::insert(int key) {
    Node *newNode = new Node{key};
    newNode->left = newNode;
    newNode->right = newNode;

    mergeWithRootList(newNode);

    if (minNode == nullptr || newNode->key < minNode->key)
        minNode = newNode;

    size++;
}

void FibonacciHeap::mergeWithRootList(Node *newNode) {
    if (rootNode == nullptr)
        rootNode = newNode;
    else {
        newNode->right = rootNode;
        newNode->left = rootNode->left;
        rootNode->left = newNode;
        newNode->left->right = newNode;
    }
}

[[maybe_unused]] int FibonacciHeap::getMin() const {
    return minNode->key;
}

bool FibonacciHeap::isEmpty() const {
    return size==0;
}

[[maybe_unused]] int FibonacciHeap::getSize() const {
    return size;
}

[[maybe_unused]] void FibonacciHeap::unionOperation(FibonacciHeap &other) {
    this->minNode = minNode->key < other.minNode->key ? minNode : other.minNode;

    Node *last = other.rootNode->left;
    other.rootNode->left = rootNode->left;
    rootNode->left->right = other.rootNode;
    rootNode->left = last;
    rootNode->left->right = rootNode;

    size += other.size;
}

int FibonacciHeap::extractMin() {
    if (!isEmpty()) {
        Node *temp = minNode;

        /// copiii nodului devin arbori noi
        if (minNode->child != nullptr) {
            /// copiii nu mai au parinti :(
            Node *child = minNode->child;
            do {
                child->parent = nullptr;
                child = child->right;
            } while (child != minNode->child);

            /// copiii integrati in lista (in societate)
            Node* firstChild = minNode->child;
            Node* lastChild = firstChild->left;
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
    return -1;
}

void FibonacciHeap::removeFromRootList(Node *x) {
    if (x == nullptr)
        return;
    if (x == rootNode)
        rootNode = rootNode->right;

    /// refac legaturile acolo unde am scos nodul
    x->right->left = x->left;
    x->left->right = x->right;
}

std::ostream &operator<<(std::ostream &os, FibonacciHeap FH) {
    Node *it = FH.rootNode;
    do {
        os << it->key << "\n";

        it = it->right;
    } while (it != FH.rootNode);
    return os;
}

void FibonacciHeap::consolidate() {
    std::vector<Node *> a(10, nullptr);
    Node *it = rootNode;
    do {
        if (it->key < minNode->key)
            minNode = it;
        Node *x = it;
        int d = x->degree;

        while (a[d] != nullptr) {
            Node *y = a[d];

            if (x->key > y->key) {
                Node *aux = x;
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

void FibonacciHeap::heapLink(Node *a, Node *b) {
    removeFromRootList(b); /// scoate nodul b din lista

    b->left = b->right = b;
    mergeWithChildList(a, b);
    a->degree++;
    b->parent = a;
}

void FibonacciHeap::mergeWithChildList(Node *parent, Node *newChild) {

    if (parent->child == nullptr) /// parintele nu are copii
        parent->child = newChild;
    else {
        newChild->right = parent->child->right;
        newChild->left = parent->child;
        parent->child->right->left = newChild;
        parent->child->right = newChild;
    }
}

void FibonacciHeap::decreaseKey(Node *x, int k) {
    if (k > x->key)
        return;
    x->key = k;
    Node *y = x->parent;
    if (y != nullptr && x->key < y->key) {/// proprietate de heap pierduta
        cut(y, x); /// taie legatura dintre x si y, x este pus in root list
        cascadingCut(y);
    }
    if (x->key < minNode->key)
        minNode = x;
}

void FibonacciHeap::cut(Node *parent, Node *node) {
    removeFromChildList(parent, node);
    parent->degree--;
    mergeWithRootList(node);
    node->parent = nullptr;
    node->marked = false;
}

void FibonacciHeap::cascadingCut(Node *node) {
    Node* parent = node->parent;
    if (parent != nullptr) {
        if (!node->marked)
            node->marked = true;
        else {
            cut(parent, node);
            cascadingCut(parent);
        }
    }
}

void FibonacciHeap::removeFromChildList(Node *parent, Node *node) {
    if (parent->child == parent->child->right) // exista doar un singur copil
        parent->child = nullptr;
    else if (parent->child == node) {
        parent->child = node->right;
        node->right->parent = parent;
    }
    node->left->right = node->right;
    node->right->left = node->left;
}

int FibonacciHeap::deleteNode(Node *x) {
    decreaseKey(x, (-0x7fffffff - 1));
    return extractMin();
}
