#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <iostream>
#include <vector>

template<typename T>
class BinaryHeap {
    private:
        std::vector<T> heap;

        inline int parent(int node);
        inline int leftSon(int node);
        inline int rightSon(int node);

        void sift(int pos);
        void percolate(int pos);

    public:
        BinaryHeap() { heap.push_back(0); }

        friend std::ostream& operator<<(std::ostream& out, const BinaryHeap& binHeap) {
            for (int i = 1; i < (int) binHeap.heap.size(); i += 1) {
                out << binHeap.heap[i] << ' ';
            }
            return out;
        }

        inline T getMin();
        void insert(T val);
        void changeKey(T val, int pos);
        void heapify(std::vector<T>& _heap);
        void eliminate(int pos);
        void merge(BinaryHeap<T>& oth);
};


#endif
