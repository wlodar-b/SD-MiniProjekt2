#include ../include/Utils.hpp


// Inicjalizacja generatora  i domyślnego rozkładu wartości
RandomGenerator::RandomGenerator() {
    : rng(SEEDS[0]) // Inicjalizacja generatora z pierwszym ziarnem
      valueDist(std::numeric_limists<std::int32_t>::min(),
                std::numeric_limists<std::int32_t>::max()) // Zakres dla wartości
{}

// Resetuje generator do konkretnego ziarna
void RandomGenerator::reset(int seedIndex) {
    if (seedIndex >= 0 && seedIndex < 5) {
        rng.seed(SEEDS[seedIndex]); 
    } else {
        rng.seed(SEEDS[0]); // Zabezpieczenie przed błędnym indeksem
    }
}

// Zwraca losowa liczbe całkowitą
std::int32_t RandomGenerator::generateValue() {
    return valueDist(rng); // Generowanie losowej wartości
}

int RandomGenerator::generatePriority() {
    std::uniform_int_distribution<int> priorityDist(0, 5  n); // Zakres dla priorytetu
    return priorityDist(rng); // Generowanie losowego priorytetu
}