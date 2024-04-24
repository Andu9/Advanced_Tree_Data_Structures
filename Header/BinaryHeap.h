#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <vector>

template<typename T>
class BinaryHeap {
private:
    std::vector<T> heap;

    inline int parent(int node);
    inline int leftSon(int node);
    inline int rightSon(int node);

public:
    inline T getMin();
};


#endif
