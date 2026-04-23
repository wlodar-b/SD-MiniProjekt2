#include "../include/PriorityList.hpp"

// Konstruktor - inicjalizuje pustą listę
PriorityList::PriorityList() : head(nullptr), tail(nullptr), size(0) {}

// Destruktor
PriorityList::~PriorityList() {
    clear(); 
}

// Konstruktor kopiujący
PriorityList::PriorityList(const PriorityList& other) : head(nullptr), tail(nullptr), size(0) {
    Node* current = other.head;
    while (current != nullptr) {
        // Dodajemy na koniec bo other jest już posortowany
        Element el = current->data;
        Node* newNode = new Node(el, nullptr, tail);
        if (tail) tail->next = newNode;
        else head = newNode; 
        tail = newNode;
        size++;
        current = current->next;
    }
}

// Operator przypisania
PriorityList& PriorityList::operator=(const PriorityList& other) {
    if (this != &other) {
        clear();
        Node* current = other.head;
        while (current != nullptr) {
            insert(current->data);
            current = current->next;
        }
    }
    return *this;
}

// Wstawianie elementu do listy
void PriorityList::insert(Element el) {
    Node* newNode = new Node(el);

    // Przypadek 1: Pusta lista
    if (!head) {
        head = tail = newNode;
    }

    // przypadek 2: Nowy element na początek
    else if (el.priority > head->data.priority) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    // Przypadek 3: Szukamy miejsca
    else {
        Node* current = head;
        // Przesuwamy się aż znajdziemy element o niższym priorytecie lub koniec listy
        while (current->next && current->next->data.priority >= el.priority) {
            current = current->next;
        }

        newNode->next = current->next;
        newNode->prev = current;
        if (current->next) current->next->prev = newNode;
        else tail = newNode; // Nowy element jest nowym ogonem

        current->next = newNode;
    }
    size++;
}

// Usuwanie i zwracanie elementu o najwyższym priorytecie
Element PriorityList::extractMax() {
    if (!head) return Element(-1, -1); // lub można rzucić wyjątek

    Element maxData = head->data;
    Node* temp = head;

    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr;

    delete temp;
    size--;
    return maxData;
}

// Podejrzenie elementy o najwyższym priorytecie 
Element PriorityList::peek() {
    if (!head) return Element(-1, -1);
    return head->data;
}

// Zmiana priorytetu elementu o danej wartości
void PriorityList::modifyKey(int val, int newPriority) {
    Node* current = head;
    while (current) {
        if (current->data.value == val) {
            // Usuwamy aktualny węzeł
            Element updatedData = current->data;
            updatedData.priority = newPriority;

            // Logika wypięcia węzła
            if (current->prev) current->prev->next = current->next;
            else head = current->next; 

            if (current->next) current->next->prev = current->prev;
            else tail = current->prev;

            delete current;
            size--;

            insert(updatedData); // Wstawiamy zaktualizowany element
            return;
        }
        current = current->next;
    }
}

// Zwrócenie rozmiaru struktury
int PriorityList::getSize() const {
    return size;
}

// Clear - czyszczenie struktury
void PriorityList::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    head = tail = nullptr;
    size = 0;
}
