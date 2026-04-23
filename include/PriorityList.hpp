#ifndef PRIORITYLIST_HPP
#define PRIORITYLIST_HPP

#include "Element.hpp" // Struktura Elementu
#include <iostream>

class PriorityList {
    private: 
        struct Node {
            Element data; // Dane przechowywane w węźle
            Node* next; // Wskaźnik na następny węzeł
            Node* prev; // Wskaźnik na poprzedni węzeł

            Node(Element el, Node* n = nullptr, Node* p = nullptr)
                : data(el), next(n), prev(p) {}
        };

        Node* head; // Wskaźnik na pierwszy węzeł listy
        Node* tail; // Wskaźnik na ostatni węzeł listy
        int size; // Liczba elementów w liście

    public:
        PriorityList();
        ~PriorityList();
        
        // Konstruktor kopiujący
        PriorityList(const PriorityList& other);

        // Operator przypisania
        PriorityList& operator=(const PriorityList& other);

        // Operacje Kolejki Priorytetowej
        void insert(Element el); // Wstawianie elementu do listy
        Element extractMax(); // Usuwanie i zwracanie elementu o najwyższym priorytecie
        Element peek(); // Zwracanie elementu o najwyższym priorytecie bez usuwania
        void modifyKey(int value, int newPriority); // Modyfikacja priorytetu elementu o danej wartości

        int getSize() const; // Zwracanie liczby elementów w liście
        void clear(); // Usuwanie wszystkich elementów z listy
        void display() const; // Wyświetlanie zawartości listy (do celów testowych)
};

#endif // PRIORITYLIST_HPP