#ifndef TIMEMEASURER_HPP
#define TIMEMEASURER_HPP

#include <chrono> // Biblioteka do pomiaru czasu
#include <functional> // Biblioteka do obsługi funkcji jako argumentów

template <typename T>
class TimeMeasurer {
    private:
        T& original; // Referencja do oryginalnej struktury danych
        int count; // Liczba powtorzeń dla jednego ziarna

    public:
        TimeMeasurer(T& original, int count) : original(original), count(count) {}

        // Metoda do pomiaru czasu wykonania operacji na strukturze danych
        long long measure(std::function<void(T&)> operation) {
            long long totalDuration = 0;
            
            for (int i = 0; i < count; ++i) {
                T copy = original; // Kopia dla pojedynczego pomiaru, bez trzymania wszystkich naraz

                // Start pomiaru czasu
                auto start = std::chrono::high_resolution_clock::now();

                operation(copy);

                // Koniec pomiaru czasu
                auto end = std::chrono::high_resolution_clock::now();

                // Mierzenie czasu trwania operacji i dodanie do sumy
                totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); 
            }

            // Zwracamy sumę, uśredmoamoe wykonamy po zebraniu wszystkich wyników z 5 seedów
            return totalDuration;
        }
};

#endif // TIMEMEASURER_HPP  