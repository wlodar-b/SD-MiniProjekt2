#include "../include/MaxHeap.hpp"

#include <iostream>
#include <stdexcept>
#include <utility>

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
    if (leftChild < heap.size() && heap[leftChild].priority > heap[largest].priority) {
        largest = leftChild;
    }
    if (rightChild < heap.size() && heap[rightChild].priority > heap[largest].priority) {
        largest = rightChild;
    }
    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}
Element MaxHeap::peek() const {
    if (heap.empty()) {
        throw std::runtime_error("Heap is empty");
    }
    return heap[0];
}
Element MaxHeap::extractMax() {
    if (heap.empty()) {
        throw std::runtime_error("Heap is empty");
    }
    Element max = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return max;
}
void MaxHeap::modifyKey(int value, int newPriority) { // zmienia PIERWSZY element o podanej wartości na nowy priorytet
    for (int i = 0; i < static_cast<int>(heap.size()); ++i) {
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
    return heap.size();
}
void MaxHeap::clear() {
    heap.clear();
}
void MaxHeap::display() const {
    for (const auto& el : heap) {
        std::cout << el.priority << " " << el.value << std::endl;
    }
}