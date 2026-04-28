#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <cstdint> // Biblioteka do obsługi typów całkowitych 

struct Element {
    int priority; // Klucz decydujący o kolejności
    int32_t value; // Wartość przechowywana w elemencie

    // Konstruktor z domyślnymi parametrami
    Element(int p = 0, std::int32_t v = 0) : priority(p), value(v) {}

    // Porównujemy elementy na podstawie ich priorytetu
    bool operator>(const Element& other) const { return priority > other.priority; }
    bool operator<(const Element& other) const { return priority < other.priority; }
    bool operator>=(const Element& other) const { return priority >= other.priority; }
    bool operator<=(const Element& other) const { return priority <= other.priority; }
    bool operator==(const Element& other) const { return priority == other.priority; }
};
#endif // ELEMENT_HPP