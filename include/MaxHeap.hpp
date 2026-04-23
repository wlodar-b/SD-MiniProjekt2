#ifndef MAXHEAP_HPP4
#define MAXHEAP_HPP4
#include <vector>
#include "Element.hpp"

class MaxHeap {
    private:
        std::vector<Element> heap;
        int capacity;
        void heapifyUp(int index);
        void heapifyDown(int index);
    public:
        MaxHeap(int c) : capacity(c) {}
        void insert(Element el)
        //reszta do dodania
}