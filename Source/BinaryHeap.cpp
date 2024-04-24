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
    return heap[0];
}


