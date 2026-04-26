#ifndef MAXHEAP_HPP
#define MAXHEAP_HPP

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
        void insert(Element el);
        Element peek() const;
        Element extractMax();
        void modifyKey(int value, int newPriority);
        int getSize() const;
        void clear();
        void display() const;
};

#endif // MAXHEAP_HPP