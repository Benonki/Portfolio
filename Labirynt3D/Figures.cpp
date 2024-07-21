/**
 * @file Figures.cpp
 * @brief Implementation of the Figures class.
 */

#include "Figures.h"

 /**
  * @brief Constructs a Figures object with default values.
  */
Figures::Figures() : Object3D(0.0f, 0.0f, 0.0f, 2.0f, 1.0f, 0.0f, 0.0f) {}

/**
 * @brief Default destructor for Figures.
 */
Figures::~Figures() = default;

/**
 * @brief Draws all figures in the figures vector.
 * @param showColoredEdges Indicates whether to show colored edges.
 */
void Figures::draw(bool showColoredEdges) {
    for (const auto& figure : figures) {
        switch (figure.rodzaj) {
        case 1:
            drawCube(figure.x, figure.y, figure.z, figure.cubeSize, figure.r, figure.g, figure.b, figure.rotationX, figure.rotationY, showColoredEdges);
            break;
        case 2:
            drawTriangle(figure.x, figure.y, figure.z, figure.cubeSize, figure.r, figure.g, figure.b, figure.rotationX, figure.rotationY, showColoredEdges);
            break;
        case 3:
            drawSphere(figure.x, figure.y, figure.z, figure.cubeSize, figure.r, figure.g, figure.b, figure.rotationX, figure.rotationY, showColoredEdges);
            break;
        case 4:
            drawStar(figure.x, figure.y, figure.z, figure.cubeSize, figure.r, figure.g, figure.b, figure.rotationX, figure.rotationY, showColoredEdges);
            break;
        case 5:
            drawMeta(figure.x, figure.y, figure.z, figure.cubeSize, figure.r, figure.g, figure.b, figure.rotationX, figure.rotationY, showColoredEdges);
            break;
        }
    }
}

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
void Figures::drawCube(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, GLfloat rotationX, GLfloat rotationY, bool showColoredEdges) {
    // Ustawienia materiału
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColor3f(r, g, b);

    // Przesunięcie i obroty
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

    // Wierzchołki sześcianu
    auto vertex = [](float dx, float dy, float dz) {
        glVertex3f(dx, dy, dz);
        };

    // Rysowanie ścian sześcianu
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    vertex(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
    vertex(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
    vertex(cubeSize / 2, cubeSize / 2, cubeSize / 2);
    vertex(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0);
    vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    vertex(cubeSize / 2, -cubeSize / 2, cubeSize / 2);
    vertex(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    vertex(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);
    vertex(cubeSize / 2, -cubeSize / 2, cubeSize / 2);
    vertex(cubeSize / 2, cubeSize / 2, cubeSize / 2);
    vertex(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    vertex(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
    vertex(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0, 0.0);
    vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    vertex(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);
    vertex(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
    vertex(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    vertex(cubeSize / 2, -cubeSize / 2, cubeSize / 2);
    vertex(cubeSize / 2, cubeSize / 2, cubeSize / 2);
    vertex(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
    glEnd();

    // Rysowanie kolorowych krawędzi
    if (showColoredEdges) {
        glLineWidth(LineWidth);
        glColor3f(LineColor[0], LineColor[1], LineColor[2]);

        glBegin(GL_LINES);

        vertex(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
        vertex(cubeSize / 2, cubeSize / 2, -cubeSize / 2);

        vertex(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
        vertex(cubeSize / 2, cubeSize / 2, cubeSize / 2);

        vertex(cubeSize / 2, cubeSize / 2, cubeSize / 2);
        vertex(-cubeSize / 2, cubeSize / 2, cubeSize / 2);

        vertex(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
        vertex(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);

        vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
        vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);

        vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
        vertex(cubeSize / 2, -cubeSize / 2, cubeSize / 2);

        vertex(cubeSize / 2, -cubeSize / 2, cubeSize / 2);
        vertex(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);

        vertex(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);
        vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);

        vertex(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
        vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);

        vertex(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
        vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);

        vertex(cubeSize / 2, cubeSize / 2, cubeSize / 2);
        vertex(cubeSize / 2, -cubeSize / 2, cubeSize / 2);

        vertex(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
        vertex(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);

        glEnd();
    }

    glPopMatrix();
}

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
void Figures::drawTriangle(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, GLfloat rotationX, GLfloat rotationY, bool showColoredEdges) {
    // Ustawienia materiału
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColor3f(r, g, b);

    // Przesunięcie i obroty
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

    // Wierzchołki trójkąta
    auto vertex = [](float dx, float dy, float dz) {
        glVertex3f(dx, dy, dz);
        };

    GLfloat halfSize = cubeSize / 2.0f;
    GLfloat height = sqrt(2.0f / 3.0f) * cubeSize;

    // Rysowanie trójkąta
    glBegin(GL_TRIANGLES);

    glNormal3f(0.0, 1.0, 0.0);
    vertex(0.0, halfSize, 0.0);
    vertex(-halfSize, -halfSize, halfSize);
    vertex(halfSize, -halfSize, halfSize);

    glNormal3f(0.0, 1.0, 0.0);
    vertex(0.0, halfSize, 0.0);
    vertex(halfSize, -halfSize, halfSize);
    vertex(0.0, -halfSize, -halfSize);

    glNormal3f(0.0, 1.0, 0.0);
    vertex(0.0, halfSize, 0.0);
    vertex(0.0, -halfSize, -halfSize);
    vertex(-halfSize, -halfSize, halfSize);

    glNormal3f(0.0, -1.0, 0.0);
    vertex(-halfSize, -halfSize, halfSize);
    vertex(0.0, -halfSize, -halfSize);
    vertex(halfSize, -halfSize, halfSize);

    glEnd();

    // Rysowanie kolorowych krawędzi
    if (showColoredEdges) {
        glLineWidth(LineWidth);
        glColor3f(LineColor[0], LineColor[1], LineColor[2]);

        glBegin(GL_LINES);

        vertex(0.0, halfSize, 0.0);
        vertex(-halfSize, -halfSize, halfSize);

        vertex(0.0, halfSize, 0.0);
        vertex(halfSize, -halfSize, halfSize);

        vertex(0.0, halfSize, 0.0);
        vertex(0.0, -halfSize, -halfSize);

        vertex(-halfSize, -halfSize, halfSize);
        vertex(halfSize, -halfSize, halfSize);

        vertex(halfSize, -halfSize, halfSize);
        vertex(0.0, -halfSize, -halfSize);

        vertex(0.0, -halfSize, -halfSize);
        vertex(-halfSize, -halfSize, halfSize);

        glEnd();
    }

    glPopMatrix();
}

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
void Figures::drawSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, GLfloat rotationX, GLfloat rotationY, bool showColoredEdges) {
    // Ustawienia materiału
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColor3f(r, g, b);

    // Przesunięcie i obroty
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

    // Rysowanie sfery
    glutSolidSphere(cubeSize / 2.0f, 50, 50);

    // Rysowanie kolorowych krawędzi
    if (showColoredEdges) {
        glLineWidth(LineWidth);
        glColor3f(LineColor[0], LineColor[1], LineColor[2]);
        glutWireSphere(cubeSize / 2.0f, 50, 50);
    }

    glPopMatrix();
}

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
void Figures::drawStar(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, GLfloat rotationX, GLfloat rotationY, bool showColoredEdges) {
    // Ustawienia materiału
    GLfloat mat_diffuse[] = { r, g, b, 0.5 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // Przesunięcie i obroty
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

    cubeSize = 0.02;
    int numberOfCubes = 5;
    showColoredEdges = false;

    // Rysowanie gwiazdy złożonej z mniejszych sześcianów
    for (int i = 0; i < numberOfCubes; ++i) {
        drawCube(0 + i * cubeSize, 0, 0, cubeSize, r, g, b, rotationX, rotationX, showColoredEdges);
        drawCube(0 - i * cubeSize, 0, 0, cubeSize, r, g, b, rotationX, rotationY, showColoredEdges);
        drawCube(0, 0, 0 + i * cubeSize, cubeSize, r, g, b, rotationX, rotationY, showColoredEdges);
        drawCube(0, 0, 0 - i * cubeSize, cubeSize, r, g, b, rotationX, rotationY, showColoredEdges);
        drawCube(0, 0 + i * cubeSize, 0, cubeSize, r, g, b, rotationX, rotationY, showColoredEdges);
        drawCube(0, 0 - i * cubeSize, 0, cubeSize, r, g, b, rotationX, rotationY, showColoredEdges);

        drawCube(0 + i * cubeSize, 0 + i * cubeSize, 0, cubeSize, r, g, b, rotationX, rotationY, showColoredEdges);
        drawCube(0 - i * cubeSize, 0 - i * cubeSize, 0, cubeSize, r, g, b, rotationX, rotationY, showColoredEdges);
        drawCube(0 + i * cubeSize, 0 - i * cubeSize, 0, cubeSize, r, g, b, rotationX, rotationY, showColoredEdges);
        drawCube(0 - i * cubeSize, 0 + i * cubeSize, 0, cubeSize, r, g, b, rotationX, rotationY, showColoredEdges);
        drawCube(0, 0 + i * cubeSize, 0 + i * cubeSize, cubeSize, r, g, b, rotationX, rotationY, showColoredEdges);
        drawCube(0, 0 + i * cubeSize, 0 - i * cubeSize, cubeSize, r, g, b, rotationX, rotationY, showColoredEdges);
        drawCube(0, 0 - i * cubeSize, 0 - i * cubeSize, cubeSize, r, g, b, rotationX, rotationY, showColoredEdges);
        drawCube(0, 0 - i * cubeSize, 0 + i * cubeSize, cubeSize, r, g, b, rotationX, rotationY, showColoredEdges);
    }
    glPopMatrix();
}

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
void Figures::drawMeta(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, GLfloat rotationX, GLfloat rotationY, bool showColoredEdges) {
    // Ustawienia materiału
    GLfloat mat_diffuse[] = { r, g, b, 0.5 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // Przesunięcie i obroty
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

    cubeSize = 0.1;
    int numberOfCubes = 6;
    showColoredEdges = true;

    // Rysowanie meta figury złożonej z mniejszych sześcianów
    for (int i = 0; i < numberOfCubes; ++i) {
        drawCube(0, (0 - 0.5) + i * cubeSize, 0, cubeSize, 0, 0, 0, 0, 0, showColoredEdges);
    }

    GLfloat flagStartY = (0 - 0.5) + numberOfCubes * cubeSize;
    int flagWidth = 5;
    int flagHeight = 3;

    // Rysowanie flagi z mniejszych sześcianów
    for (int i = 0; i < flagHeight; ++i) {
        for (int j = 0; j < flagWidth; ++j) {
            if ((i + j) % 2 == 0) {
                drawCube(0 + (j * cubeSize), flagStartY + (i * cubeSize), 0, cubeSize, 1, 1, 1, 0, 0, showColoredEdges);
            }
            else {
                drawCube(0 + (j * cubeSize), flagStartY + (i * cubeSize), 0, cubeSize, 0, 0, 0, 0, 0, showColoredEdges);
            }
        }
    }
    glPopMatrix();
}

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
void Figures::addFigure(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, GLfloat rotationX, GLfloat rotationY, int rodzaj) {
    figures.emplace_back(x, y, z, cubeSize, r, g, b, rotationX, rotationY, rodzaj);
}

/**
 * @brief Resets the figures vector by clearing it.
 */
void Figures::resetCubes() {
    figures.clear();
}

/**
 * @brief Removes the last figure from the figures vector.
 */
void Figures::removeLastCube() {
    if (!figures.empty()) {
        figures.pop_back();
    }
}

/**
 * @brief Removes figures by their size.
 * @param size Size of the figure to remove.
 */
void Figures::removeFigureBySize(GLfloat size) {
    figures.erase(std::remove_if(figures.begin(), figures.end(), [size](const FiguresStruct& figure) {
        return figure.cubeSize == size;
        }), figures.end());
}
