# Struktury Danych - Miniprojekt 2
**Temat:** Kolejka Priorytetowa (MAX Priority Queue)    
**Technologia:** C++ (Standard ISO), Programowanie Obiektowe   
**Cel:** Implementacja struktur danych bez użycia biblioteki STL oraz analiza ich wydajności czasowej.

---

## Opis projektu
Projekt obejmuje własną implementację Kolejki Priorytetowej typu MAX opartej na dwóch różnych strukturach danych:
1. **Kopiec Binarny (Max Heap):** Implementacja wymagana dla uzyskania oceny 5.0.
2. **Posortowana Lista Dwukierunkowa:** Struktura porównawcza z elementami ułożonymi w porządku malejącym.

Wszystkie struktury są alokowane dynamicznie, a ich rozmiar jest modyfikowany przy każdej operacji dodawania lub usuwania elementów.

---

## Zaimplementowane Operacje
* `insert(e, p)` – Dodanie elementu o wartości *e* z priorytetem *p*.
* `extract-max()` – Usunięcie i zwrócenie elementu o najwyższym priorytecie.
* `peek()` / `find-max()` – Podgląd elementu o najwyższym priorytecie bez usuwania.
* `modify-key(e, p)` – Zmiana priorytetu wybranego elementu.
* `return-size` – Zwrócenie aktualnej liczby elementów w kolejce.

---

## Metodologia Badań
Pomiary czasu są przeprowadzane zgodnie z rygorystycznymi wytycznymi:
* **Jednostka:** Nanosekundy [ns].
* **Statystyka:** Każdy wynik jest średnią ze 150 pomiarów (5 różnych ziarn/seedów x 30 powtórzeń dla każdego ziarna).
* **Skalowalność:** Badania obejmują minimum 8 punktów pomiarowych, zaczynając od $n \ge 5000$ elementów.
* **Dane:** Priorytety są generowane losowo z zakresu kilkukrotnie większego niż wielkość struktury.
* **Izolacja:** Operacje `insert` i `extract-max` są mierzone na kopiach struktury, aby zachować stały rozmiar *n* podczas pomiaru.

---

## 📂 Struktura Projektu
```text
.
├── include/           # Pliki nagłówkowe (*.hpp)
├── src/               # Implementacja (*.cpp)
├── data/              # Wyniki pomiarów w formacie *.txt
└── README.md          # Dokumentacja projektu