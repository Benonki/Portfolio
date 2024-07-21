/**
 * @file Figures.h
 * @brief Declaration of the Figures class and related structures.
 */

#pragma once
#ifndef FIGURES_H
#define FIGURES_H

#include <GL/glew.h>
#include <vector>
#include <cmath>
#include "Object3D.h"

 /**
  * @brief Struct representing a figure with various attributes.
  */
struct FiguresStruct {
    GLfloat x; /**< X position of the figure. */
    GLfloat y; /**< Y position of the figure. */
    GLfloat z; /**< Z position of the figure. */
    GLfloat cubeSize; /**< Size of the cube. */
    GLfloat r; /**< Red color component. */
    GLfloat g; /**< Green color component. */
    GLfloat b; /**< Blue color component. */
    GLfloat rotationX; /**< Rotation angle around the X axis. */
    GLfloat rotationY; /**< Rotation angle around the Y axis. */
    int rodzaj; /**< Type of the figure. */

    /**
     * @brief Constructs a FiguresStruct with specified attributes.
     * @param x X position of the figure.
     * @param y Y position of the figure.
     * @param z Z position of the figure.
     * @param cubeSize Size of the cube.
     * @param r Red color component.
     * @param g Green color component.
     * @param b Blue color component.
     * @param rotationX Rotation angle around the X axis.
     * @param rotationY Rotation angle around the Y axis.
     * @param rodzaj Type of the figure.
     */
    FiguresStruct(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, GLfloat rotationX, GLfloat rotationY, int rodzaj)
        : x(x), y(y), z(z), cubeSize(cubeSize), r(r), g(g), b(b), rotationX(rotationX), rotationY(rotationY), rodzaj(rodzaj) {}
};

/**
 * @brief Class representing a collection of 3D figures.
 */
class Figures : public Object3D {
public:
    Figures();
    ~Figures();

    /**
     * @brief Draws all figures in the figures vector.
     * @param showColoredEdges Indicates whether to show colored edges.
     */
    void draw(bool showColoredEdges) override;

    /**
     * @brief Draws a cube.
     * @param x X position.
     * @param y Y position.
     * @param z Z position.
     * @param cubeSize Size of the cube.
     * @param r Red color component.
     * @param g Green color component.
     * @param b Blue color component.
     * @param rotationX Rotation around the X axis.
     * @param rotationY Rotation around the Y axis.
     * @param showColoredEdges Indicates whether to show colored edges.
     */
    void drawCube(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, GLfloat rotationX, GLfloat rotationY, bool showColoredEdges);

    /**
    * @brief Draws a triangle.
    * @param x X position.
    * @param y Y position.
    * @param z Z position.
    * @param cubeSize Size of the triangle.
    * @param r Red color component.
    * @param g Green color component.
    * @param b Blue color component.
    * @param rotationX Rotation around the X axis.
    * @param rotationY Rotation around the Y axis.
    * @param showColoredEdges Indicates whether to show colored edges.
    */
    void drawTriangle(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, GLfloat rotationX, GLfloat rotationY, bool showColoredEdges);

    /**
     * @brief Draws a sphere.
     * @param x X position.
     * @param y Y position.
     * @param z Z position.
     * @param cubeSize Size of the sphere.
     * @param r Red color component.
     * @param g Green color component.
     * @param b Blue color component.
     * @param rotationX Rotation around the X axis.
     * @param rotationY Rotation around the Y axis.
     * @param showColoredEdges Indicates whether to show colored edges.
     */
    void drawSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, GLfloat rotationX, GLfloat rotationY, bool showColoredEdges);

    /**
     * @brief Draws a star.
     * @param x X position.
     * @param y Y position.
     * @param z Z position.
     * @param cubeSize Size of the star.
     * @param r Red color component.
     * @param g Green color component.
     * @param b Blue color component.
     * @param rotationX Rotation around the X axis.
     * @param rotationY Rotation around the Y axis.
     * @param showColoredEdges Indicates whether to show colored edges.
     */
    void drawStar(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, GLfloat rotationX, GLfloat rotationY, bool showColoredEdges);

    /**
     * @brief Draws a meta figure.
     * @param x X position.
     * @param y Y position.
     * @param z Z position.
     * @param cubeSize Size of the figure.
     * @param r Red color component.
     * @param g Green color component.
     * @param b Blue color component.
     * @param rotationX Rotation around the X axis.
     * @param rotationY Rotation around the Y axis.
     * @param showColoredEdges Indicates whether to show colored edges.
     */
    void drawMeta(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, GLfloat rotationX, GLfloat rotationY, bool showColoredEdges);

    /**
    * @brief Adds a new figure to the figures vector.
    * @param x X position.
    * @param y Y position.
    * @param z Z position.
    * @param cubeSize Size of the figure.
    * @param r Red color component.
    * @param g Green color component.
    * @param b Blue color component.
    * @param rotationX Rotation around the X axis.
    * @param rotationY Rotation around the Y axis.
    * @param rodzaj Type of the figure.
    */
    void addFigure(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, GLfloat rotationX, GLfloat rotationY, int rodzaj);

    /**
     * @brief Resets the figures vector by clearing it.
     */
    void resetCubes();

    /**
     * @brief Removes the last figure from the figures vector.
     */
    void removeLastCube();

    /**
     * @brief Removes figures by their size.
     * @param size Size of the figure to remove.
     */
    void removeFigureBySize(GLfloat size);

    /**
     * @brief Gets the figures vector.
     * @return Vector of figures.
     */
    std::vector<FiguresStruct> getFigures() const { return figures; }

private:
    std::vector<FiguresStruct> figures; /**< Vector storing the figures. */
    GLfloat LineWidth = 3.0f; /**< Line width. */
    GLfloat LineColor[3] = { 0.0f, 0.0f, 0.0f }; /**< Line color. */
};

#endif // FIGURES_H
