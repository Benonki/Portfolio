/**
 * @file main.cpp
 *
 * @brief Główny plik programu 3DSandbox.
 */

#include "Engine3D.h"

 /**
  * @brief Funkcja główna programu.
  *
  * @param argc Liczba argumentów wiersza poleceń.
  * @param argv Tablica argumentów wiersza poleceń.
  *
  * @return Kod zakończenia programu.
  */
int main(int argc, char** argv) {
    /**
     * @brief Inicjalizacja obiektu 3D Engine.
     */
    Engine3D engine;

    /**
     * @brief Uruchomienie silnika 3D z przekazanymi argumentami wiersza poleceń.
     */
    engine.run(argc, argv);

    /**
     * @brief Zakończenie programu z kodem 0.
     */
    return 0;
}
