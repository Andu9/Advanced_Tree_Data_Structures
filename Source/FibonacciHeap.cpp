//
// Created by Cosmin on 24.04.2024.
//

#include "FibonacciHeap.h"

void FibonacciHeap::insert(int key) {
     Node *newNode = new Node{key};
     newNode->left = newNode;
     newNode->right = newNode;

     mergeList(newNode);

     if (minNode == nullptr || newNode->key < minNode->key)
         minNode = newNode;

     size++;
}

void FibonacciHeap::mergeList(Node *newNode) {
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

int FibonacciHeap::getSize() const {
    return size;
}

void FibonacciHeap::unionOperation(FibonacciHeap &other) {
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
        if (minNode->child != nullptr) {
            minNode->child->left->right = rootNode;
            minNode->child->left = rootNode->left;
            rootNode->left = minNode->child->left;
            minNode->child->left->right = minNode->child;
            minNode->child = nullptr;
        }

        if (minNode->right == minNode) { /// era singurul nod in toata lista
            minNode = nullptr;
            rootNode = nullptr;
        }
        else {
            minNode = minNode->right;
            removeFromList(minNode);
            consolidate();
        }
        size--;
        return temp->key;
    }
    return -1;
}

void FibonacciHeap::removeFromList(Node *x) {
    if (x == nullptr)
        return;
    if (x == rootNode)
        rootNode = rootNode->right;
    x->right->left = x->left;
    x->left->right = x->right;
}

std::ostream &operator<<(std::ostream &os, FibonacciHeap FH) {
    os << FH.minNode->key;
    return os;
}

void FibonacciHeap::consolidate() {
    std::vector<Node *> a(int(log(size) * 2), nullptr);
    Node *it = rootNode;
    do {
        int d = it->degree;
        if (a[d] == nullptr)
            a[d] = it;
        else { /// exista deja un nod cu numarul respectiv de copii
            Node *aux = a[d];

            if (aux->key < it->key) /// arborele nou ca si copil pentru arborele vechi
                heapLink(aux, it);
            else /// arborele vechi ca si copil pentru arborele nou
                heapLink(it, aux);

        }
        it = it->right;
    } while (it != rootNode);
}

void FibonacciHeap::heapLink(Node *a, Node *b) {
    removeFromList(b);
}


