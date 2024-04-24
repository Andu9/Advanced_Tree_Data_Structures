#include "../Header/BinaryHeap.h"

template<typename T>
inline int BinaryHeap<T>::parent(int node) {
    return node >> 1;
}

template<typename T>
inline int BinaryHeap<T>::leftSon(int node) {
    return node << 1;
}

template<typename T>
inline int BinaryHeap<T>::rightSon(int node) {
    return (node << 1) | 1;
}

template<typename T>
inline T BinaryHeap<T>::getMin() {
    return heap[1];
}

template<typename T>
void BinaryHeap<T>::sift(int pos) {
    int son, Size = heap.size() - 1;
    do {
        son = 0;

        int leftChild = leftSon(pos);
        if (leftChild <= Size) {
            son = leftChild;

            int rightChild = rightSon(pos);
            if (rightChild <= Size && heap[rightChild] < heap[leftChild]) {
                son = rightChild;
            }

            if (heap[son] >= heap[pos]) {
                son = 0;
            }
        }

        if (son != 0) {
            std::swap(heap[son], heap[pos]);
            pos = son;
        }
    }while(son != 0);
}

template<typename T>
void BinaryHeap<T>::percolate(int pos) {
    int val = heap[pos];

    int _parent = parent(pos);
    while (pos > 1 && val < heap[_parent]) {
        heap[pos] = heap[_parent];
        pos = _parent, _parent = parent(pos);
    }

    heap[pos] = val;
}

template<typename T>
void BinaryHeap<T>::insert(T val) {
    heap.emplace_back(val);
    percolate(int(heap.size() - 1));
}

template<typename T>
void BinaryHeap<T>::changeKey(T val, int pos) {
    T currentValue = heap[pos];
    heap[pos] = val;

    if (val < currentValue) {
        percolate(pos);
    } else if (val > currentValue) {
        sift(pos);
    }
}

template<typename T>
void BinaryHeap<T>::heapify(std::vector<T>& _heap) {
    heap = _heap;
    for (int i = heap.size() - 1; i >= 1; i -= 1) {
        sift(i);
    }
}

template<typename T>
void BinaryHeap<T>::eliminate(int pos) {
    heap[pos] = heap[heap.size() - 1];
    heap.pop_back();

    int _parent = parent(pos);
    if (pos > 1 && heap[pos] < heap[_parent]) {
        percolate(pos);
    } else {
        sift(pos);
    }
}

template class BinaryHeap<int>;

