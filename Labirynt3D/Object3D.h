/**
 * @file Object3D.h
 * @brief Declaration of the Object3D class.
 */

#pragma once
#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <GL/freeglut.h>

 /**
  * @brief Abstract class representing a 3D object.
  */
class Object3D {
public:
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
    Object3D(GLfloat x, GLfloat y, GLfloat z, GLfloat size, GLfloat r, GLfloat g, GLfloat b);
    virtual ~Object3D() = default;

    /**
     * @brief Pure virtual method to draw the 3D object.
     * @param showColoredEdges Indicates whether to show colored edges.
     */
    virtual void draw(bool showColoredEdges) = 0;

protected:
    GLfloat x; /**< X position of the object. */
    GLfloat y; /**< Y position of the object. */
    GLfloat z; /**< Z position of the object. */
    GLfloat size; /**< Size of the object. */
    GLfloat r; /**< Red color component. */
    GLfloat g; /**< Green color component. */
    GLfloat b; /**< Blue color component. */
};

#endif // OBJECT3D_H
