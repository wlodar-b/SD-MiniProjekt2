#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint> // Biblioteka do obsługi typów całkowitych o określonej szerokości
#include <limits> // Biblioteka do obsługi limitów typów danych
#include <random> // Biblioteka do generowania liczb losowych

class RandomGenerator {
    private:
        // 5 stałych seedów 
        static constexpr std::uint32_t SEEDS[5] = {
            123456789u,
            987654321u,
            555666777u,
            111222333u,
            444333222u
        };
        std::mt19937 rng; // Generator Mersenne Twister
        std::uniform_int_distribution<std::int32_t> valueDist; // Rozkład do generowania liczb całkowitych

    public:
        RandomGenerator();

        void reset(int seedIndex = 0); // Reset generatora z określonym seedem

        // Generowanie losowej liczby
        std::int32_t generateValue();

        // Generowanie losowego priorytetu
        int generatePriority(int n); 
    };
#endif // UTILS_HPP