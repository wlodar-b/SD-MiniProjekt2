#ifndef MAXHEAP_HPP
#define MAXHEAP_HPP

#include "Element.hpp"

class MaxHeap {
    private:
        Element* heap;
        int capacity;
        int size;
        void heapifyUp(int index);
        void heapifyDown(int index);
    public:
        MaxHeap(int c);
        MaxHeap(const MaxHeap& other);
        MaxHeap& operator=(const MaxHeap& other);
        ~MaxHeap();

        void insert(Element el);
        Element peek() const;
        Element extractMax();
        void modifyKey(int value, int newPriority);
        int getSize() const;
        void clear();
        void display() const;
};

#endif // MAXHEAP_HPP