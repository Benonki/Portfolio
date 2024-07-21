#pragma once

#include <GL/freeglut.h>

/**
 * @brief Klasa reprezentująca ogólny obiekt 3D.
 *
 * Klasa ta zawiera podstawowe informacje o obiekcie 3D, takie jak położenie, rozmiar oraz kolor.
 */
class Object3D {
private:
    GLfloat x; ///< Współrzędna X obiektu 3D.
    GLfloat y; ///< Współrzędna Y obiektu 3D.
    GLfloat z; ///< Współrzędna Z obiektu 3D.
    GLfloat size; ///< Rozmiar obiektu 3D.
    GLfloat r; ///< Składowa czerwona koloru obiektu.
    GLfloat g; ///< Składowa zielona koloru obiektu.
    GLfloat b; ///< Składowa niebieska koloru obiektu.

public:
    /**
     * @brief Konstruktor klasy Object3D.
     *
     * @param x Współrzędna X obiektu 3D.
     * @param y Współrzędna Y obiektu 3D.
     * @param z Współrzędna Z obiektu 3D.
     * @param size Rozmiar obiektu 3D.
     * @param r Składowa czerwona koloru obiektu.
     * @param g Składowa zielona koloru obiektu.
     * @param b Składowa niebieska koloru obiektu.
     */
    Object3D(GLfloat x, GLfloat y, GLfloat z, GLfloat size, GLfloat r, GLfloat g, GLfloat b);

    /**
     * @brief Destruktor klasy Object3D.
     */
    ~Object3D();
};
