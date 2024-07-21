/**
 * @file Object3D.cpp
 * @brief Implementation of the Object3D class.
 */

#include "Object3D.h"

 /**
 * @brief Constructs an Object3D with specified attributes.
 * @param x X position of the object.
 * @param y Y position of the object.
 * @param z Z position of the object.
 * @param size Size of the object.
 * @param r Red color component.
 * @param g Green color component.
 * @param b Blue color component.
 */
Object3D::Object3D(GLfloat x, GLfloat y, GLfloat z, GLfloat size, GLfloat r, GLfloat g, GLfloat b)
    : x(x), y(y), z(z), size(size), r(r), g(g), b(b) {}
