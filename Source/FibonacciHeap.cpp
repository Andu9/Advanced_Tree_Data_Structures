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

        /// copiii nodului devin arbori noi
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
            minNode = minNode->right; /// temporar, clar incorect
            removeFromList(minNode->left);
            consolidate(); /// aici se stabileste adevarata valoare minima noua
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

//    unvisited = deque()
//    root_list = []
//    marked_nodes = []
//
//    if self.root_list:
//    for node in self.iterate(self.root_list):
//    root_list.append(node.key)
//    unvisited.append(node)
//
//    print('--------------------')
//    print('-- Fibonacci Heap --')
//    print('--------------------')
//    print(f'Total nodes: {self.n}')
//    print(f'Minimum: {self.min.key if self.min else None}')
//    print(f'Root list node: {self.root_list.key}')
//    print(f'Root list: {root_list}')
//
//    while unvisited:
//        node = unvisited.popleft()
//    if node.mark and (node.key not in marked_nodes):
//    marked_nodes.append(node.key)
//    if node.child:
//    children = []
//    for child in self.iterate(node.child):
//    children.append(child.key)
//    if child.child:
//    unvisited.append(child)
//    if child.mark and (child.key not in marked_nodes):
//    marked_nodes.append(child.key)
//    print(f'Children of {node.key}: {children}')
//    if print_marked:
//        print(f'Marked nodes: {marked_nodes}')
//    print('--------------------\n')

}

void FibonacciHeap::consolidate() {
    std::vector<Node *> a(int(log(size) * 2), nullptr);
    Node *it = rootNode;
    do {
        Node *urm = it->right;
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

        it = urm;
    } while (it != rootNode);

//    for w in range(0, len(nodes)):
//        x = nodes[w]
//        d = x.degree
//        while A[d] != None:
//            y = A[d]
//            if x.key > y.key:
//                temp = x
//                x, y = y, temp
//            self.heap_link(y, x)
//            A[d] = None
//            d += 1
//        A[d] = x

}

void FibonacciHeap::heapLink(Node *a, Node *b) {
    removeFromList(b); /// scoate nodul b din lista

    b->left = b->right = b;
    mergeWithChildList(a, b);
    a->degree++;
    b->parent = a;

//    self.remove_from_root_list(y)
//    y.left = y.right = y
//    self.merge_with_child_list(x, y)
//    x.degree += 1
//    y.parent = x
//    y.mark = False

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

//    if parent.child is None:
//    parent.child = node
//    else:
//    node.right = parent.child.right
//    node.left = parent.child
//    parent.child.right.left = node
//    parent.child.right = node
}


