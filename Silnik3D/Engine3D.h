/**
 * @file Engine3D.h
 *
 * @brief Plik nagłówkowy programu 3DSandbox pliku Engine3D.cpp.
 */

#pragma once

#ifndef ENGINE3D_H
#define ENGINE3D_H

#include <GL/freeglut.h>
#include <string>
#include <iostream>
#include <locale.h>
#include <algorithm>
#include "Figures.h"
#include <Windows.h>

/**
 * @brief Klasa reprezentująca silnik trójwymiarowy.
 */
class Engine3D {
private:
    GLfloat cubeSize; /**< Rozmiar sześcianu. */
    GLfloat cameraDistance; /**< Odległość kamery od środka sceny. */
    GLfloat cameraAngleX; /**< Kąt obrotu kamery wokół osi X. */
    GLfloat cameraAngleY; /**< Kąt obrotu kamery wokół osi Y. */
    GLfloat cameraPositionX; /**< Pozycja kamery w osi X. */
    GLfloat cameraPositionY; /**< Pozycja kamery w osi Y. */
    GLfloat cameraPositionZ; /**< Pozycja kamery w osi Z. */
    GLfloat cubeX; /**< Pozycja X sześcianu. */
    GLfloat cubeY; /**< Pozycja Y sześcianu. */
    GLfloat cubeZ; /**< Pozycja Z sześcianu. */
    GLfloat ColorR; /**< Składowa czerwona koloru. */
    GLfloat ColorG; /**< Składowa zielona koloru. */
    GLfloat ColorB; /**< Składowa niebieska koloru. */
    bool isSpeedPressed; /**< Flaga wciśnięcia klawisza szybkości kamery. */
    bool isMouseDragging; /**< Flaga przeciągania myszy. */
    int framePerSecond; /**< Liczba klatek na sekundę. */
    int lastMouseX; /**< Ostatnia pozycja X myszy. */
    int lastMouseY; /**< Ostatnia pozycja Y myszy. */
    bool keys[256]; /**< Tablica stanu klawiszy. */
    float cameraSpeed; /**< Szybkość kamery. */
    bool isRotating; /**< Flaga obrotu sceny. */
    bool showColoredEdges; /**< Flaga rysowania krawędzi w kolorze. */
    bool lightingEnabled; /**< Flaga włączenia oświetlenia. */
    bool shadingEnabled; /**< Flaga włączenia cieniowania. */
    float rotationAngleX; /**< Kąt obrotu wokół osi X. */
    float rotationAngleY; /**< Kąt obrotu wokół osi Y. */
    Figures* MyFigure; /**< Wskaźnik do obiektu przechowującego figury. */

public:
    /**
     * @brief Konstruktor klasy Engine3D.
     */
    Engine3D();

    /**
     * @brief Destruktor klasy Engine3D.
     */
    ~Engine3D();

    /**
     * @brief Metoda zwracająca instancję silnika trójwymiarowego.
     * @return Wskaźnik do instancji silnika.
     */
    static Engine3D* getEngineInstance();

    /**
     * @brief Metoda statyczna do aktualizacji kamery.
     * @param value Wartość do przekazania w funkcji czasowej.
     */
    static void staticUpdateCamera(int value);

    /**
     * @brief Metoda statyczna do wyświetlania sceny.
     */
    static void staticDisplay();

    /**
     * @brief Metoda statyczna do dostosowania widoku w zależności od zmiany rozmiaru okna.
     * @param width Szerokość okna.
     * @param height Wysokość okna.
     */
    static void staticReshape(int width, int height);

    /**
     * @brief Metoda statyczna obsługująca zdarzenia myszy.
     * @param button Kod przycisku.
     * @param state Stan przycisku.
     * @param x Pozycja X myszy.
     * @param y Pozycja Y myszy.
     */
    static void staticMouse(int button, int state, int x, int y);

    /**
     * @brief Metoda statyczna obsługująca ruch myszy.
     * @param x Pozycja X myszy.
     * @param y Pozycja Y myszy.
     */
    static void staticMotion(int x, int y);

    /**
     * @brief Metoda statyczna obsługująca klawiaturę.
     * @param key Wciśnięty klawisz.
     * @param x Pozycja X kursora.
     * @param y Pozycja Y kursora.
     */
    static void staticKeyboard(unsigned char key, int x, int y);

    /**
     * @brief Metoda statyczna obsługująca zwolnienie klawisza klawiatury.
     * @param key Zwolniony klawisz.
     * @param x Pozycja X kursora.
     * @param y Pozycja Y kursora.
     */
    static void staticKeyboardUp(unsigned char key, int x, int y);

    /**
     * @brief Inicjalizuje ustawienia OpenGL.
     */
    void init();

    /**
     * @brief Resetuje stan sześcianów i kamery.
     */
    void resetCubes();

    /**
     * @brief Ustawia pozycję sześcianu w zależności od kamery.
     */
    void SetCubeCord();

    /**
     * @brief Pobiera wartości koloru od użytkownika.
     */
    void inputRGB();

    /**
     * @brief Rysuje wszystkie figury w scenie.
     */
    void drawAllFigures();

    /**
     * @brief Wyświetla scenę.
     */
    void display();

    /**
     * @brief Dostosowuje widok w zależności od zmiany rozmiaru okna.
     * @param width Szerokość okna.
     * @param height Wysokość okna.
     */
    void reshape(int width, int height);

    /**
     * @brief Obsługuje zdarzenia myszy.
     * @param button Kod przycisku.
     * @param state Stan przycisku.
     * @param x Pozycja X myszy.
     * @param y Pozycja Y myszy.
     */
    void mouse(int button, int state, int x, int y);

    /**
     * @brief Obsługuje ruch myszy.
     * @param x Pozycja X myszy.
     * @param y Pozycja Y myszy.
     */
    void motion(int x, int y);

    /**
     * @brief Obsługuje klawiaturę.
     * @param key Wciśnięty klawisz.
     * @param x Pozycja X kursora.
     * @param y Pozycja Y kursora.
     */
    void keyboard(unsigned char key, int x, int y);

    /**
     * @brief Obsługuje zwolnienie klawisza klawiatury.
     * @param key Zwolniony klawisz.
     * @param x Pozycja X kursora.
     * @param y Pozycja Y kursora.
     */
    void keyboardUp(unsigned char key, int x, int y);

    /**
     * @brief Aktualizuje pozycję kamery.
     * @param value Wartość do przekazania w funkcji czasowej.
     */
    void updateCamera(int value);

    /**
     * @brief Zmienia liczbę klatek na sekundę.
     */
    void changeFPS();

    /**
     * @brief Uruchamia silnik trójwymiarowy.
     * @param argc Liczba argumentów wiersza poleceń.
     * @param argv Tablica argumentów wiersza poleceń.
     */
    void run(int argc, char** argv);
};

#endif // ENGINE3D_H
