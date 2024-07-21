#include "Object3D.h"

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
Object3D::Object3D(GLfloat x, GLfloat y, GLfloat z, GLfloat size, GLfloat r, GLfloat g, GLfloat b)
    : x(x), y(y), z(z), size(size), r(r), g(g), b(b) {}

/**
 * @brief Destruktor klasy Object3D.
 *
 * Destruktor nie wykonuje dodatkowych operacji, ponieważ nie ma potrzeby zwalniania zasobów.
 */
Object3D::~Object3D() {}
