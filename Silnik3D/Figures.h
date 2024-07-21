/**
 * @file Figures.h
 *
 * @brief Plik nagłówkowy programu 3DSandbox pliku Figures.cpp.
 */

#pragma once
#ifndef CUBE_H
#define CUBE_H

#include "Object3D.h"
#include <vector>

/**
 * @brief Struktura reprezentująca figurę w trójwymiarowej przestrzeni.
 */
struct FiguresStruct {
    GLfloat x, y, z, cubeSize, r, g, b, rodzaj; /**< Pozycja, rozmiar, i kolor figury, oraz jej rodzaj. */
    FiguresStruct(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, int rodzaj) : x(x), y(y), z(z), cubeSize(cubeSize), r(r), g(g), b(b), rodzaj(rodzaj) {} /**< Konstruktor struktury FiguresStruct. */
};

/**
 * @brief Klasa reprezentująca figury w trójwymiarowej przestrzeni.
 */
class Figures : public Object3D {
private:
    std::vector<FiguresStruct> figures; /**< Wektor przechowujący figury. */
    GLfloat LineWidth; /**< Grubość linii dla krawędzi. */
    GLfloat LineColor[3]; /**< Kolor linii dla krawędzi. */

public:
    /**
     * @brief Konstruktor klasy Figures.
     */
    Figures();

    /**
     * @brief Destruktor klasy Figures.
     */
    ~Figures();

    /**
     * @brief Metoda zwracająca wektor figur.
     * @return Wektor figur.
     */
    const std::vector<FiguresStruct>& getFigures() const { return figures; }

    /**
     * @brief Metoda rysująca sześcian.
     * @param x Współrzędna x środka sześcianu.
     * @param y Współrzędna y środka sześcianu.
     * @param z Współrzędna z środka sześcianu.
     * @param cubeSize Rozmiar sześcianu.
     * @param r Składowa czerwona koloru.
     * @param g Składowa zielona koloru.
     * @param b Składowa niebieska koloru.
     * @param showColoredEdges Określa, czy rysować krawędzie w kolorze.
     */
    void drawCube(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, bool showColoredEdges);

    /**
     * @brief Metoda rysująca trójkąt.
     * @param x Współrzędna x środka trójkąta.
     * @param y Współrzędna y środka trójkąta.
     * @param z Współrzędna z środka trójkąta.
     * @param cubeSize Rozmiar trójkąta.
     * @param r Składowa czerwona koloru.
     * @param g Składowa zielona koloru.
     * @param b Składowa niebieska koloru.
     * @param showColoredEdges Określa, czy rysować krawędzie w kolorze.
     */
    void drawTriangle(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, bool showColoredEdges);

    /**
     * @brief Metoda rysująca sferę.
     * @param x Współrzędna x środka sfery.
     * @param y Współrzędna y środka sfery.
     * @param z Współrzędna z środka sfery.
     * @param cubeSize Rozmiar sfery.
     * @param r Składowa czerwona koloru.
     * @param g Składowa zielona koloru.
     * @param b Składowa niebieska koloru.
     * @param showColoredEdges Określa, czy rysować krawędzie w kolorze.
     */
    void drawSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, bool showColoredEdges);

    /**
     * @brief Metoda dodająca nową figurę do wektora.
     * @param x Współrzędna x środka figury.
     * @param y Współrzędna y środka figury.
     * @param z Współrzędna z środka figury.
     * @param cubeSize Rozmiar figury.
     * @param r Składowa czerwona koloru.
     * @param g Składowa zielona koloru.
     * @param b Składowa niebieska koloru.
     * @param rodzaj Rodzaj figury (1-sześcian, 2-trójkąt, 3-sfera).
     */
    void addFigure(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, int rodzaj);

    /**
     * @brief Metoda resetująca wektor figur.
     */
    void resetCubes();

    /**
     * @brief Metoda usuwająca ostatnią figurę z wektora.
     */
    void removeLastCube();
};
#endif // CUBE_H
