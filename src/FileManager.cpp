#include "../include/FileManager.hpp"
#include "../include/Utils.hpp" // Potrzebne do RandomGenerator
#include <fstream>
#include <iostream>
#include <stdexcept>

// Tworzy plik o strukturze:
// [liczba_elementów]
// [priorytet_1] [wartosc_1]
// [priorytet_2] [wartosc_2]
void FileManager::generateInputFile(const std::string& filename, int n) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Nie mozna utworzyc pliku: " + filename);
    }

    RandomGenerator rng;
    file << n << "\n";
    for (int i = 0; i < n; ++i) {
        file << rng.generatePriority(n) << " " << rng.generateValue() << "\n";
    }
    
    file.close();
    std::cout << "Wygenerowano plik: " << filename << " z " << n << " elementami." << std::endl;
}

std::vector<Element> FileManager::loadFromFile(const std::string& filename) {
    std::vector<Element> elements;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Nie mozna otworzyc pliku: " + filename);
    }

    int n;
    if (!(file >> n)) return elements;

    elements.reserve(n);
    int p, v;
    for (int i = 0; i < n; ++i) {
        if (file >> p >> v) {
            elements.emplace_back(p, v);
        }
    }
    
    file.close();
    return elements;
}

void FileManager::saveToCSV(const std::string& filename, const std::string& structureName, 
                            const std::string& operationName, int n, long long timeNs) {
    // ios::app otwiera plik w trybie dopisywania
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Blad: Nie udalo sie otworzyc pliku CSV do zapisu." << std::endl;
        return;
    }

    // Dodanie nagłówka, jeśli plik jest pusty
    file.seekp(0, std::ios::end);
    if (file.tellp() == 0) {
        file << "Structure,Operation,N,Time_ns\n";
    }

    // Zapis w formacie: MaxHeap,insert,10000,124500
    file << structureName << "," << operationName << "," << n << "," << timeNs << "\n";
    
    file.close();
}