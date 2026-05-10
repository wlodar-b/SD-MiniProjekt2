#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>
#include <vector>
#include "Element.hpp"

class FileManager {
public:
    // Tworzy plik .txt z losowymi danymi (zgodnie z FAQ)
    static void generateInputFile(const std::string& filename, int n);

    // Wczytuje dane z pliku (potrzebne do opcji "zbuduj z pliku")
    static std::vector<Element> loadFromFile(const std::string& filename);

    // Zapisuje wyniki pomiarów do CSV z flagą append (dopisuje na końcu pliku)
    static void saveToCSV(const std::string& filename, const std::string& structureName, 
                          const std::string& operationName, int n, long long timeNs);
};

#endif // FILEMANAGER_HPP