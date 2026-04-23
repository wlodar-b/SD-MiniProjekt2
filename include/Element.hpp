#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <cstdint> // Biblioteka do obsługi typów całkowitych 

struct Element {
    int priority; // Klucz decydujący o kolejności
    std::int32_t value; // Wartość przechowywana w elemencie

    // Konstruktor
    Element() : priority(0), value(0) {}

    // Konstruktor z parametrami
    Element(int p, std::int32_t v) : priority(p), value(v) {}

    // Operatorzy porównania ułatwiające implementację struktur


    bool operator>(const Element& other) const {
        return priority > other.priority; 
    }

    bool operator<(const Element& other) const {
        return priority < other.priority; 
    }
     
    bool operator>=(const Element& other) const {
        return priority >= other.priority; 
    }

    bool operator<=(const Element& other) const {
        return priority <= other.priority; 
    }

    bool operator==(const Element& other) const {
        return priority == other.priority; 
    }

};

#endif // ELEMENT_HPP