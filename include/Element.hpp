#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <cstdint> // Biblioteka do obsługi typów całkowitych 

struct Element {
    int priority; // Klucz decydujący o kolejności
    std::int32_t value; // Wartość przechowywana w elemencie
    Element(int p = 0, std::int32_t v = 0) : priority(p), value(v) {}
};
#endif // ELEMENT_HPP