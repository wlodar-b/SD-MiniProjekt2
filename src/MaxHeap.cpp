#include "../include/MaxHeap.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>

MaxHeap::MaxHeap(int c) : heap(new Element[c]), capacity(c), size(0) {}

MaxHeap::MaxHeap(const MaxHeap& other)
    : heap(new Element[other.capacity]), capacity(other.capacity), size(other.size) {
    if (size > 0) {
        std::copy(other.heap, other.heap + size, heap);
    }
}

MaxHeap& MaxHeap::operator=(const MaxHeap& other) {
    if (this != &other) {
        Element* newHeap = new Element[other.capacity];
        if (other.size > 0) {
            std::copy(other.heap, other.heap + other.size, newHeap);
        }

        delete[] heap;
        heap = newHeap;
        capacity = other.capacity;
        size = other.size;
    }
    return *this;
}

MaxHeap::~MaxHeap() {
    delete[] heap;
}

void MaxHeap::insert(Element el) {
    if (size >= capacity) {
        throw std::runtime_error("Heap is full");
    }
    heap[size] = el;
    heapifyUp(size);
    ++size;
}

void MaxHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index -1) / 2;
        if (heap[index].priority <= heap[parent].priority) {
            break;
        }
        std::swap(heap[index], heap[parent]);
        index = parent;
    }
}
void MaxHeap::heapifyDown(int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int largest = index;
    if (leftChild < size && heap[leftChild].priority > heap[largest].priority) {
        largest = leftChild;
    }
    if (rightChild < size && heap[rightChild].priority > heap[largest].priority) {
        largest = rightChild;
    }
    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}
Element MaxHeap::peek() const {
    if (size == 0) {
        throw std::runtime_error("Heap is empty");
    }
    return heap[0];
}
Element MaxHeap::extractMax() {
    if (size == 0) {
        throw std::runtime_error("Heap is empty");
    }
    Element max = heap[0];
    heap[0] = heap[size - 1];
    --size;
    if (size > 0) {
        heapifyDown(0);
    }
    return max;
}
void MaxHeap::modifyKey(int value, int newPriority) { // zmienia PIERWSZY element o podanej wartości na nowy priorytet
    for (int i = 0; i < size; ++i) {
        if (heap[i].value == value) {
            int oldPriority = heap[i].priority;
            heap[i].priority = newPriority;

            if (newPriority > oldPriority) {
                heapifyUp(i);
            } else {
                heapifyDown(i);
            }
            return;
        }
    }
}
int MaxHeap::getSize() const {
    return size;
}
void MaxHeap::clear() {
    size = 0;
}
void MaxHeap::display() const {
    for (int i = 0; i < size; ++i) {
        std::cout << heap[i].priority << " " << heap[i].value << std::endl;
    }
}