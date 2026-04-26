#ifndef TIMEMEASURER_HPP
#define TIMEMEASURER_HPP

#include <chrono> // Biblioteka do pomiaru czasu
#include <vector> // Biblioteka do przechowywania wyników pomiarów
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
            std::vector<T> copies;
            copies.reserve(count);
            for (int i = 0; i < count; ++i) {
                copies.push_back(original); // Tworzenie kopii oryginalnej struktury danych
            }

            long long totalDuration = 0;
            
            for (int i = 0; i < count; ++i) {
                // Start pomiaru czasu
                auto start = std::chrono::high_resolution_clock::now();

                operation(copies[i]);

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