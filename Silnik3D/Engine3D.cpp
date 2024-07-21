/**
 * @file Engine3D.cpp
 *
 * @brief Plik programu 3DSandbox, zawierający znaczną część operacji, wykonywanych w silniku graficznym.
 */

#include "Engine3D.h"

Engine3D::Engine3D() :
    cubeSize(2.0f),
    cameraDistance(5.0f),
    cameraAngleX(0.0f),
    cameraAngleY(0.0f),
    cameraPositionX(0.0f),
    cameraPositionY(0.0f),
    cameraPositionZ(0.0f),
    cubeX(0.0),
    cubeY(0.0),
    cubeZ(0.0),
    ColorR(1.0),
    ColorG(0.0),
    ColorB(0.0),
    isSpeedPressed(false),
    isMouseDragging(false),
    framePerSecond(16),
    lastMouseX(0),
    lastMouseY(0),
    cameraSpeed(0.05),
    isRotating(false),
    showColoredEdges(false),
    lightingEnabled(true),
    shadingEnabled(true),
    rotationAngleX(0),
    rotationAngleY(0),
    MyFigure(new Figures())
{ /* Konstruktor */
}

Engine3D::~Engine3D() {
    resetCubes();
    delete MyFigure;
}

Engine3D* Engine3D::getEngineInstance() {
    static Engine3D engineInstance;
    return &engineInstance;
}

void Engine3D::staticUpdateCamera(int value) {
    getEngineInstance()->updateCamera(value);
}

void Engine3D::staticDisplay() {
    getEngineInstance()->display();
}

void Engine3D::staticReshape(int width, int height) {
    getEngineInstance()->reshape(width, height);
}

void Engine3D::staticMouse(int button, int state, int x, int y) {
    getEngineInstance()->mouse(button, state, x, y);
}

void Engine3D::staticMotion(int x, int y) {
    getEngineInstance()->motion(x, y);
}

void Engine3D::staticKeyboard(unsigned char key, int x, int y) {
    getEngineInstance()->keyboard(key, x, y);
}

void Engine3D::staticKeyboardUp(unsigned char key, int x, int y) {
    getEngineInstance()->keyboardUp(key, x, y);
}

void Engine3D::init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glShadeModel(GL_SMOOTH);
}

void Engine3D::resetCubes() {
    if (MyFigure) {
        MyFigure->resetCubes();
    }

    cameraDistance = 5.0f;
    cameraAngleX = 0.0f;
    cameraAngleY = 0.0f;
    cameraPositionX = 0.0f;
    cameraPositionY = 0.0f;
    cameraPositionZ = 0.0f;
}

void Engine3D::SetCubeCord() {
    GLfloat distanceInFrontOfCamera = 5.0f;
    GLfloat dirX = sin(cameraAngleY * 3.14159265 / 180.0);
    GLfloat dirY = sin(cameraAngleX * 3.14159265 / 180.0);
    GLfloat dirZ = cos(cameraAngleY * 3.14159265 / 180.0);
    cubeX = cameraPositionX + dirX * distanceInFrontOfCamera;
    cubeY = cameraPositionY + dirY * distanceInFrontOfCamera;
    cubeZ = cameraPositionZ + dirZ * distanceInFrontOfCamera;
}

void Engine3D::inputRGB() {
    system("cls");

    auto inputColorValue = [](float& colorValue, const char* colorName) {
        do {
            std::cout << "Wprowadź wartość " << colorName << " (0-1): ";
            std::cin >> colorValue;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                colorValue = -1;
            }
        } while (colorValue < 0 || colorValue > 1);
        };

    inputColorValue(ColorR, "R");
    inputColorValue(ColorG, "G");
    inputColorValue(ColorB, "B");
}

void Engine3D::drawAllFigures() {
    for (const auto& figure : MyFigure->getFigures()) {
        if (figure.rodzaj == 1) {
            glPushMatrix();
            glTranslatef(figure.x, figure.y, figure.z);
            glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f);
            glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f);
            MyFigure->drawCube(figure.x, figure.y, figure.z, figure.cubeSize, figure.r, figure.g, figure.b, showColoredEdges);
            glPopMatrix();
        }
        else if (figure.rodzaj == 2) MyFigure->drawTriangle(figure.x, figure.y, figure.z, figure.cubeSize, figure.r, figure.g, figure.b, showColoredEdges);
        else if (figure.rodzaj == 3) MyFigure->drawSphere(figure.x, figure.y, figure.z, figure.cubeSize, figure.r, figure.g, figure.b, showColoredEdges);
    }
}

void Engine3D::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(
        cameraPositionX, cameraPositionY, cameraPositionZ,
        cameraPositionX + cameraDistance * sin(cameraAngleY * 3.14159265 / 180.0),
        cameraPositionY + cameraDistance * sin(cameraAngleX * 3.14159265 / 180.0),
        cameraPositionZ + cameraDistance * cos(cameraAngleY * 3.14159265 / 180.0),
        0.0, 1.0, 0.0
    );

    if (isRotating) {
        static float rotationAngleX = 0.0f;
        static float rotationAngleY = 0.0f;
        rotationAngleX += 0.5f;
        rotationAngleY += 0.5f;

        glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f);
    }

    drawAllFigures();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(0.0f, 0.0f, 0.0f);

    std::string cameraCoords = "X: " + std::to_string(cameraPositionX) +
        " Y: " + std::to_string(cameraPositionY) +
        " Z: " + std::to_string(cameraPositionZ);
    glRasterPos2f(10, glutGet(GLUT_WINDOW_HEIGHT) - 20);
    for (char c : cameraCoords) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
    }

    std::string fpsText = "FPS: " + std::to_string(static_cast<int>(1000 / framePerSecond));
    glRasterPos2f(glutGet(GLUT_WINDOW_WIDTH) - 80, glutGet(GLUT_WINDOW_HEIGHT) - 20);
    for (char c : fpsText) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
    }

    const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    std::string versionText = "OpenGL Version: " + std::string(version);
    glRasterPos2f(10, glutGet(GLUT_WINDOW_HEIGHT) - 590);
    for (char c : versionText) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glutSwapBuffers();
}

void Engine3D::reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void Engine3D::mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isMouseDragging = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else if (state == GLUT_UP) {
            isMouseDragging = false;
        }
    }
    else if (button == 3) {
        cubeSize += 0.1f;
    }
    else if (button == 4) {
        if (cubeSize > 0.1) cubeSize -= 0.1f;
    }
}

void Engine3D::motion(int x, int y) {
    if (isMouseDragging) {
        cameraAngleX -= (y - lastMouseY) * 0.5;
        cameraAngleY -= (x - lastMouseX) * 0.5;

        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay();
    }
}

void Engine3D::keyboard(unsigned char key, int x, int y) {
    keys[key] = true;
    key = std::tolower(key);
    switch (key) {
    case '0':
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        resetCubes();
        break;
    case '1':
        SetCubeCord();
        MyFigure->addFigure(cubeX, cubeY, cubeZ, cubeSize, ColorR, ColorG, ColorB, 1);
        break;
    case '2':
        SetCubeCord();
        MyFigure->addFigure(cubeX, cubeY, cubeZ, cubeSize, ColorR, ColorG, ColorB, 2);
        break;
    case '3':
        SetCubeCord();
        MyFigure->addFigure(cubeX, cubeY, cubeZ, cubeSize, ColorR, ColorG, ColorB, 3);
        break;
    case 'f':
        showColoredEdges = !showColoredEdges;
        break;
    case 'r':
        isRotating = !isRotating;
        break;
    case 'z':
        changeFPS();
        break;
    case 'p':
        lightingEnabled = !lightingEnabled;
        if (lightingEnabled) {
            glEnable(GL_LIGHTING);
        }
        else {
            glDisable(GL_LIGHTING);
        }
        break;
    case 'l':
        shadingEnabled = !shadingEnabled;
        if (shadingEnabled) {
            glShadeModel(GL_SMOOTH);
            glEnable(GL_DEPTH_TEST);
        }
        else {
            glShadeModel(GL_FLAT);
            glDisable(GL_DEPTH_TEST);
        }
        break;
    case 'k':
        inputRGB();
        break;
    case 'n':
        MyFigure->removeLastCube();
        break;
    case 'x':
        isSpeedPressed = !isSpeedPressed;
        break;
    case '6':
        rotationAngleY += 10.0f;
        break;
    case '7':
        rotationAngleX += 10.0f;
        break;
    case '8':
        rotationAngleY -= 10.0f;
        break;
    case '9':
        rotationAngleX -= 10.0f;
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

void Engine3D::keyboardUp(unsigned char key, int x, int y) {
    keys[key] = false;
}

void Engine3D::updateCamera(int value) {
    cameraSpeed = (isSpeedPressed ? 0.25f : 0.05f);
    if (keys['w'] || keys['W']) {
        cameraPositionX += cameraSpeed * sin(cameraAngleY * 3.14159265 / 180.0);
        cameraPositionZ += cameraSpeed * cos(cameraAngleY * 3.14159265 / 180.0);
    }
    if (keys['s'] || keys['S']) {
        cameraPositionX -= cameraSpeed * sin(cameraAngleY * 3.14159265 / 180.0);
        cameraPositionZ -= cameraSpeed * cos(cameraAngleY * 3.14159265 / 180.0);
    }
    if (keys['a'] || keys['A']) {
        cameraPositionX += cameraSpeed * cos(cameraAngleY * 3.14159265 / 180.0);
        cameraPositionZ -= cameraSpeed * sin(cameraAngleY * 3.14159265 / 180.0);
    }
    if (keys['d'] || keys['D']) {
        cameraPositionX -= cameraSpeed * cos(cameraAngleY * 3.14159265 / 180.0);
        cameraPositionZ += cameraSpeed * sin(cameraAngleY * 3.14159265 / 180.0);
    }
    if (keys[' ']) {
        cameraPositionY += 0.1;
    }
    if (keys['c'] || keys['C']) {
        cameraPositionY -= 0.1;
    }

    glutTimerFunc(framePerSecond, staticUpdateCamera, 0);

    glutPostRedisplay();
}

void Engine3D::changeFPS() {
    if (framePerSecond == 16) framePerSecond = 32;
    else if (framePerSecond == 32) framePerSecond = 8;
    else if (framePerSecond == 8) framePerSecond = 16;
}

void Engine3D::run(int argc, char** argv) {
    setlocale(LC_ALL, "polish");
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);  
    glutInitWindowPosition(100, 100);  
    glutCreateWindow("OpenGL 3D Engine");

    init();

    glutDisplayFunc(staticDisplay);
    glutReshapeFunc(staticReshape);
    glutMouseFunc(staticMouse);
    glutMotionFunc(staticMotion);
    glutKeyboardFunc(staticKeyboard);
    glutKeyboardUpFunc(staticKeyboardUp);

    glutTimerFunc(framePerSecond, staticUpdateCamera, 0);

    glutMainLoop();
}
