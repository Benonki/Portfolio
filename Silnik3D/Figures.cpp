/**
 * @file Figures.cpp
 *
 * @brief Plik programu 3DSandbox, zawierający wszelkie elementy związane z figurami 3D.
 */

#include "Figures.h"

 /**
  * @brief Konstruktor klasy Figures inicjujący obiekt 3D o domyślnych wartościach.
  */
Figures::Figures() : Object3D(0.0f, 0.0f, 0.0f, 2.0f, 1.0f, 0.0f, 0.0f) {}

/**
 * @brief Destruktor klasy Figures.
 */
Figures::~Figures() {}

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
void Figures::drawCube(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, bool showColoredEdges) {
    glEnable(GL_NORMALIZE);
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);


    auto vertex = [x, y, z](float dx, float dy, float dz) {
        glVertex3f(x + dx, y + dy, z + dz);
        };

    //Ściana Górna
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    vertex(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
    vertex(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
    vertex(cubeSize / 2, cubeSize / 2, cubeSize / 2);
    vertex(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
    glEnd();

    //Ściana Dolna 
    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0);
    vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    vertex(cubeSize / 2, -cubeSize / 2, cubeSize / 2);
    vertex(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);
    glEnd();

    //Ściana na Przodzie 
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    vertex(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);
    vertex(cubeSize / 2, -cubeSize / 2, cubeSize / 2);
    vertex(cubeSize / 2, cubeSize / 2, cubeSize / 2);
    vertex(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
    glEnd();

    //Ściana Tylna 
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    vertex(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
    vertex(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
    glEnd();

    //Ściana Lewa
    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0, 0.0);
    vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    vertex(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);
    vertex(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
    vertex(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
    glEnd();

    //Ściana Prawa 
    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    vertex(cubeSize / 2, -cubeSize / 2, cubeSize / 2);
    vertex(cubeSize / 2, cubeSize / 2, cubeSize / 2);
    vertex(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
    glEnd();

    if (showColoredEdges) {
        glLineWidth(LineWidth);
        glColor3f(LineColor[0], LineColor[1], LineColor[2]);

        glBegin(GL_LINES);

        //krawędzie dla ściany górnej
        vertex(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
        vertex(cubeSize / 2, cubeSize / 2, -cubeSize / 2);

        vertex(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
        vertex(cubeSize / 2, cubeSize / 2, cubeSize / 2);

        vertex(cubeSize / 2, cubeSize / 2, cubeSize / 2);
        vertex(-cubeSize / 2, cubeSize / 2, cubeSize / 2);

        vertex(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
        vertex(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);

        //krawędzie dla ściany dolnej
        vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
        vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);

        vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
        vertex(cubeSize / 2, -cubeSize / 2, cubeSize / 2);

        vertex(cubeSize / 2, -cubeSize / 2, cubeSize / 2);
        vertex(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);

        vertex(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);
        vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);

        //krawędzie łączące ściany górne i dolne
        vertex(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
        vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);

        vertex(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
        vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);

        vertex(cubeSize / 2, cubeSize / 2, cubeSize / 2);
        vertex(cubeSize / 2, -cubeSize / 2, cubeSize / 2);

        vertex(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
        vertex(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);

        //krawędzie dla ścian bocznych
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
}

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
void Figures::drawTriangle(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, bool showColoredEdges) {
    glEnable(GL_NORMALIZE);
    glBegin(GL_TRIANGLES);

    auto vertex = [x, y, z](float dx, float dy, float dz) {
        glVertex3f(x + dx, y + dy, z + dz);
        };

    //Ściana 1 
    glColor3f(r, g, b);
    vertex(0.0, -cubeSize / 2, cubeSize / 2);
    vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);

    //Ściana 2 
    vertex(0.0, -cubeSize / 2, cubeSize / 2);
    vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    vertex(0.0, cubeSize / 2, 0.0);

    //Ściana 3 
    vertex(0.0, -cubeSize / 2, cubeSize / 2);
    vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    vertex(0.0, cubeSize / 2, 0.0);

    //Ściana 4 
    vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
    vertex(0.0, cubeSize / 2, 0.0);

    glEnd();

    if (showColoredEdges) {
        glLineWidth(LineWidth);
        glColor3f(LineColor[0], LineColor[1], LineColor[2]);

        glBegin(GL_LINES);

        //krawędzię dla trójkąta 
        vertex(0.0, -cubeSize / 2, cubeSize / 2);
        vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);

        vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
        vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);

        vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
        vertex(0.0, -cubeSize / 2, cubeSize / 2);

        vertex(0.0, -cubeSize / 2, cubeSize / 2);
        vertex(0.0, cubeSize / 2, 0.0);

        vertex(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
        vertex(0.0, cubeSize / 2, 0.0);

        vertex(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
        vertex(0.0, cubeSize / 2, 0.0);

        glEnd();
    }
}

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
void Figures::drawSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, bool showColoredEdges) {
    glEnable(GL_NORMALIZE);
    int slices = 30;
    int stacks = 30;

    auto vertex = [x, y, z](float dx, float dy, float dz) {
        glVertex3f(x + dx, y + dy, z + dz);
        };

    if (showColoredEdges) {
        glLineWidth(LineWidth);
        glColor3f(LineColor[0], LineColor[1], LineColor[2]);

        glBegin(GL_LINES);

        for (int i = 0; i <= slices; ++i) {
            for (int j = 0; j < stacks; ++j) {
                float theta1 = (i * 2 * 3.14159265) / slices;
                float theta2 = ((i + 1) * 2 * 3.14159265) / slices;
                float phi = (j * 3.14159265) / stacks;
                float phi2 = ((j + 1) * 3.14159265) / stacks;

                float x1 = sin(phi) * cos(theta1) * cubeSize / 2;
                float y1 = cos(phi) * cubeSize / 2;
                float z1 = sin(phi) * sin(theta1) * cubeSize / 2;

                float x2 = sin(phi) * cos(theta2) * cubeSize / 2;
                float y2 = cos(phi) * cubeSize / 2;
                float z2 = sin(phi) * sin(theta2) * cubeSize / 2;

                float x3 = sin(phi2) * cos(theta1) * cubeSize / 2;
                float y3 = cos(phi2) * cubeSize / 2;
                float z3 = sin(phi2) * sin(theta1) * cubeSize / 2;

                float x4 = sin(phi2) * cos(theta2) * cubeSize / 2;
                float y4 = cos(phi2) * cubeSize / 2;
                float z4 = sin(phi2) * sin(theta2) * cubeSize / 2;

                vertex(x1, y1, z1);
                vertex(x2, y2, z2);

                vertex(x2, y2, z2);
                vertex(x3, y3, z3);

                vertex(x3, y3, z3);
                vertex(x4, y4, z4);

                vertex(x4, y4, z4);
                vertex(x1, y1, z1);
            }
        }

        glEnd();
    }


    glPushMatrix();
    glTranslatef(x, y, z);

    glColor3f(r, g, b);
    GLfloat mat_diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glutSolidSphere(cubeSize / 2, slices, stacks);

    glPopMatrix();
}

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
void Figures::addFigure(GLfloat x, GLfloat y, GLfloat z, GLfloat cubeSize, GLfloat r, GLfloat g, GLfloat b, int rodzaj) {
    figures.emplace_back(x, y, z, cubeSize, r, g, b, rodzaj);
}

/**
 * @brief Metoda resetująca wektor figur.
 */
void Figures::resetCubes() {
    figures.clear();
}

/**
 * @brief Metoda usuwająca ostatnią figurę z wektora.
 */
void Figures::removeLastCube() {
    if (!figures.empty()) {
        figures.pop_back();
    }
}