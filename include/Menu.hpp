#ifndef MENU_HPP
#define MENU_HPP

#include "MaxHeap.hpp" // Implementacja kopca maksymalnego
#include "PriorityList.hpp" // Implementacja listy priorytetowej
#include "Utils.hpp"

class Menu {
    private:
        MaxHeap heap; // Obiekt kopca maksymalnego
        PriorityList priorityList; // Obiekt listy priorytetowej

        RandomGenerator rng; // Obiekt generatora liczb losowych
        
        void menuHeap(); // Obiekt menu kopca
        void menuList(); // Obiektu menu listy priorytetowej

        // Miejsce na metody pomocnicze


    public:
        void DisplayMainMenu(); // Metoda wyświetlająca główne menu
};


#endif // MENU_HPP
