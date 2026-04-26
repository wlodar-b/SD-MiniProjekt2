#include "../include/Menu.hpp"
#include "../include/TimeMeasurer.hpp"

#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace {
    constexpr int ALL_SEEDS = 5;

    enum class Operation {
        Insert = 1,
        ExtractMax = 2,
        Peek = 3,
        ModifyKey = 4,
        GetSize = 5,
        All = 6
    };

    int readInt(const std::string& prompt) {
        int value;
        std::cout << prompt;

        while (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Niepoprawna wartosc. Sprobuj ponownie: ";
        }

        return value;
    }

    int readPositiveInt(const std::string& prompt) {
        int value = readInt(prompt);
        while (value <= 0) {
            std::cout << "Wartosc musi byc wieksza od 0." << std::endl;
            value = readInt(prompt);
        }
        return value;
    }

    int readSeedChoice() {
        int seed = readInt("Seed (0-4) albo 5 = wszystkie seedy: ");
        while (seed < 0 || seed > ALL_SEEDS) {
            std::cout << "Seed musi byc z zakresu 0-5." << std::endl;
            seed = readInt("Seed (0-4) albo 5 = wszystkie seedy: ");
        }
        return seed;
    }

    Operation readOperationChoice() {
        std::cout << "\nWybierz operacje do pomiaru:" << std::endl;
        std::cout << "1. insert" << std::endl;
        std::cout << "2. extractMax" << std::endl;
        std::cout << "3. peek" << std::endl;
        std::cout << "4. modifyKey" << std::endl;
        std::cout << "5. getSize" << std::endl;
        std::cout << "6. wszystkie operacje" << std::endl;

        int choice = readInt("Wybor: ");
        while (choice < 1 || choice > 6) {
            std::cout << "Niepoprawny wybor." << std::endl;
            choice = readInt("Wybor: ");
        }
        return static_cast<Operation>(choice);
    }

    std::vector<Element> generateElements(RandomGenerator& rng, int n) {
        std::vector<Element> elements;
        elements.reserve(n);

        for (int i = 0; i < n; ++i) {
            elements.emplace_back(rng.generatePriority(n), rng.generateValue());
        }

        return elements;
    }

    MaxHeap buildHeap(const std::vector<Element>& elements) {
        MaxHeap heap(static_cast<int>(elements.size()) + 1);
        for (const Element& element : elements) {
            heap.insert(element);
        }
        return heap;
    }

    PriorityList buildList(const std::vector<Element>& elements) {
        PriorityList list;
        for (const Element& element : elements) {
            list.insert(element);
        }
        return list;
    }

    std::string operationName(Operation operation) {
        switch (operation) {
            case Operation::Insert:
                return "insert";
            case Operation::ExtractMax:
                return "extractMax";
            case Operation::Peek:
                return "peek";
            case Operation::ModifyKey:
                return "modifyKey";
            case Operation::GetSize:
                return "getSize";
            case Operation::All:
                return "wszystkie";
        }
        return "nieznana";
    }

    template <typename Structure, typename Builder>
    long long measureOperation(
        Operation operation,
        RandomGenerator& rng,
        int n,
        int repeatCount,
        int seedChoice,
        Builder builder
    ) {
        int firstSeed = seedChoice == ALL_SEEDS ? 0 : seedChoice;
        int lastSeed = seedChoice == ALL_SEEDS ? ALL_SEEDS - 1 : seedChoice;
        long long totalTime = 0;

        for (int seed = firstSeed; seed <= lastSeed; ++seed) {
            rng.reset(seed);
            std::vector<Element> elements = generateElements(rng, n);
            Structure original = builder(elements);
            Element elementToInsert(rng.generatePriority(n + 1), rng.generateValue());
            int valueToModify = elements[n / 2].value;
            int newPriority = rng.generatePriority(n + 1);

            TimeMeasurer<Structure> measurer(original, repeatCount);
            volatile int sink = 0;

            switch (operation) {
                case Operation::Insert:
                    totalTime += measurer.measure([&](Structure& structure) {
                        structure.insert(elementToInsert);
                    });
                    break;
                case Operation::ExtractMax:
                    totalTime += measurer.measure([&](Structure& structure) {
                        Element removed = structure.extractMax();
                        sink += removed.priority;
                    });
                    break;
                case Operation::Peek:
                    totalTime += measurer.measure([&](Structure& structure) {
                        Element max = structure.peek();
                        sink += max.priority;
                    });
                    break;
                case Operation::ModifyKey:
                    totalTime += measurer.measure([&](Structure& structure) {
                        structure.modifyKey(valueToModify, newPriority);
                    });
                    break;
                case Operation::GetSize:
                    totalTime += measurer.measure([&](Structure& structure) {
                        sink += structure.getSize();
                    });
                    break;
                case Operation::All:
                    break;
            }
        }

        return totalTime;
    }

    template <typename Structure, typename Builder>
    void printMeasurement(
        const std::string& structureName,
        Operation operation,
        RandomGenerator& rng,
        int n,
        int repeatCount,
        int seedChoice,
        Builder builder
    ) {
        int seedCount = seedChoice == ALL_SEEDS ? ALL_SEEDS : 1;
        long long totalTime = measureOperation<Structure>(operation, rng, n, repeatCount, seedChoice, builder);
        long long measurementCount = static_cast<long long>(repeatCount) * seedCount;

        std::cout << structureName << " | " << operationName(operation)
                  << " | suma: " << totalTime << " ns"
                  << " | srednia: " << totalTime / measurementCount << " ns" << std::endl;
    }

    template <typename Structure, typename Builder>
    void runMeasurementsForStructure(
        const std::string& structureName,
        RandomGenerator& rng,
        Builder builder
    ) {
        int n = readPositiveInt("Liczba elementow n: ");
        int repeatCount = readPositiveInt("Liczba powtorzen dla seeda: ");
        int seedChoice = readSeedChoice();
        Operation operation = readOperationChoice();

        std::cout << "\nWyniki pomiarow:" << std::endl;

        if (operation == Operation::All) {
            long long totalForAll = 0;
            for (int op = static_cast<int>(Operation::Insert); op <= static_cast<int>(Operation::GetSize); ++op) {
                Operation currentOperation = static_cast<Operation>(op);
                long long totalTime = measureOperation<Structure>(
                    currentOperation,
                    rng,
                    n,
                    repeatCount,
                    seedChoice,
                    builder
                );
                int seedCount = seedChoice == ALL_SEEDS ? ALL_SEEDS : 1;
                long long measurementCount = static_cast<long long>(repeatCount) * seedCount;

                totalForAll += totalTime;
                std::cout << structureName << " | " << operationName(currentOperation)
                          << " | suma: " << totalTime << " ns"
                          << " | srednia: " << totalTime / measurementCount << " ns" << std::endl;
            }
            std::cout << "Czas laczny wszystkich operacji: " << totalForAll << " ns" << std::endl;
        } else {
            printMeasurement<Structure>(structureName, operation, rng, n, repeatCount, seedChoice, builder);
        }
    }

    void runComparison(RandomGenerator& rng) {
        int n = readPositiveInt("Liczba elementow n: ");
        int repeatCount = readPositiveInt("Liczba powtorzen dla seeda: ");
        int seedChoice = readSeedChoice();
        Operation operation = readOperationChoice();

        std::cout << "\nPorownanie struktur:" << std::endl;

        if (operation == Operation::All) {
            for (int op = static_cast<int>(Operation::Insert); op <= static_cast<int>(Operation::GetSize); ++op) {
                Operation currentOperation = static_cast<Operation>(op);
                printMeasurement<MaxHeap>("MaxHeap", currentOperation, rng, n, repeatCount, seedChoice, buildHeap);
                printMeasurement<PriorityList>("PriorityList", currentOperation, rng, n, repeatCount, seedChoice, buildList);
            }
        } else {
            printMeasurement<MaxHeap>("MaxHeap", operation, rng, n, repeatCount, seedChoice, buildHeap);
            printMeasurement<PriorityList>("PriorityList", operation, rng, n, repeatCount, seedChoice, buildList);
        }
    }
}

Menu::Menu() : heap(1), priorityList(), rng() {}

void Menu::DisplayMainMenu() {
    int choice;

    do {
        std::cout << "\n===== MENU GLOWNE =====" << std::endl;
        std::cout << "1. Pomiary dla MaxHeap" << std::endl;
        std::cout << "2. Pomiary dla PriorityList" << std::endl;
        std::cout << "3. Porownaj obie struktury" << std::endl;
        std::cout << "0. Wyjscie" << std::endl;

        choice = readInt("Wybor: ");

        switch (choice) {
            case 1:
                menuHeap();
                break;
            case 2:
                menuList();
                break;
            case 3:
                runComparison(rng);
                break;
            case 0:
                std::cout << "Koniec programu." << std::endl;
                break;
            default:
                std::cout << "Niepoprawny wybor." << std::endl;
                break;
        }
    } while (choice != 0);
}

void Menu::menuHeap() {
    runMeasurementsForStructure<MaxHeap>("MaxHeap", rng, buildHeap);
}

void Menu::menuList() {
    runMeasurementsForStructure<PriorityList>("PriorityList", rng, buildList);
}
