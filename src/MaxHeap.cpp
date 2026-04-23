#include "../include/MaxHeap.hpp"

void MaxHeap::insert(Element el) {
    if (heap.size() >= capacity) { 
        throw std::runtime_error("Heap is full");
    }
    heap.push_back(el);
    heapifyUp(heap.size() - 1);
}

void MaxHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index -1) / 2;
        if (heap[index].priority <= heap[parent].priority) {
            break
        }
        std::swap(heap[index], heap[parent]);
        index = parent;
    }
}
// do zrobienia reszta funkcji