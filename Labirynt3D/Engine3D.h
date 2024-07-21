/**
 * @file Engine3D.h
 * @brief Declaration of the Engine3D class and related functions.
 */

#pragma once
#ifndef ENGINE3D_H
#define ENGINE3D_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SFML/Audio.hpp>
#include <GL/glut.h>
#include "Figures.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string>

#define SHADOW_WIDTH 1024
#define SHADOW_HEIGHT 1024

 /**
  * @brief Class representing a 3D engine for rendering and managing figures.
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
    int StarCounter; /**< Licznik gwiazdek. */
    int CurrQuickColor; /**< Aktualny szybki kolor. */
    bool keys[256]; /**< Tablica stanu klawiszy. */
    float cameraSpeed; /**< Szybkość kamery. */
    bool showColoredEdges; /**< Flaga rysowania krawędzi w kolorze. */
    bool shadingEnabled; /**< Flaga włączenia cieniowania. */
    bool AdminMode; /**< Flaga trybu administratora. */
    bool CollisionMode; /**< Flaga trybu kolizji. */
    bool Level1Completed; /**< Flaga ukończenia poziomu 1. */
    bool Level2Completed; /**< Flaga ukończenia poziomu 2. */
    bool showExtra; /**< Flaga wyświetlania dodatkowych informacji. */
    bool TriggerUsed; /**< Flaga użycia triggera. */
    bool WhUsed; /**< Flaga użycia WH. */
    clock_t startTime; /**< Czas rozpoczęcia. */
    clock_t endTime; /**< Czas zakończenia. */
    clock_t TimeForTrigger; /**< Czas na trigger. */
    float elapsedTime; /**< Upływający czas. */
    float rotationAngleX; /**< Kąt obrotu wokół osi X. */
    float rotationAngleY; /**< Kąt obrotu wokół osi Y. */
    Figures* MyFigure; /**< Wskaźnik do obiektu przechowującego figury. */
    GLuint depthMapFBO; /**< Frame buffer obiektu mapy głębi. */
    GLuint depthMap; /**< Mapa głębi. */
    int selectedFigureType; /**< Wybrany typ figury. */
    bool isPlacingFigure; /**< Flaga umieszczania figury. */
    GLfloat previewRotationX; /**< Kąt obrotu podglądu wokół osi X. */
    GLfloat previewRotationY; /**< Kąt obrotu podglądu wokół osi Y. */
    GLfloat previewX; /**< Pozycja X podglądu. */
    GLfloat previewY; /**< Pozycja Y podglądu. */
    GLfloat previewZ; /**< Pozycja Z podglądu. */
    int selectedFPS; /**< Wybrane klatki na sekundę. */
    float baseCameraSpeed; /**< Bazowa szybkość kamery. */
    sf::Music backgroundMusic; /**< Muzyka w tle. */
    bool musicMuted; /**< Flaga wyciszenia muzyki. */
    bool showMenu; /**< Flaga wyświetlania menu. */
    int menuSelection; /**< Wybór menu. */
    int scrollOffset; /**< Przesunięcie przewijania. */
    int scrollIncrement; /**< Przyrost przewijania. */
    bool lightingEnabled; /**< Flaga włączenia oświetlenia. */
    std::string displayMessage; /**< Wiadomość do wyświetlenia. */
    time_t messageStartTime; /**< Czas rozpoczęcia wyświetlania wiadomości. */
    bool isDepthTestDisabled; /**< Flaga wyłączenia testu głębokości. */
    time_t depthTestDisableStartTime; /**< Czas rozpoczęcia wyłączenia testu głębokości. */
    float depthTestDisableDuration; /**< Czas trwania wyłączenia testu głębokości. */

public:
    /**
     * @brief Constructs the Engine3D object.
     */
    Engine3D();

    /**
     * @brief Destroys the Engine3D object.
     */
    ~Engine3D();

    /**
     * @brief Gets the singleton instance of the Engine3D.
     * @return Pointer to the Engine3D instance.
     */
    static Engine3D* getEngineInstance();

    /**
     * @brief Static method to update the camera.
     * @param value Integer value.
     */
    static void staticUpdateCamera(int value);

    /**
     * @brief Static method to display the scene.
     */
    static void staticDisplay();

    /**
     * @brief Static method to handle window reshape.
     * @param width New width of the window.
     * @param height New height of the window.
     */
    static void staticReshape(int width, int height);

    /**
     * @brief Static method to handle mouse input.
     * @param button Mouse button.
     * @param state State of the button.
     * @param x X position of the mouse.
     * @param y Y position of the mouse.
     */
    static void staticMouse(int button, int state, int x, int y);

    /**
     * @brief Static method to handle mouse motion.
     * @param x X position of the mouse.
     * @param y Y position of the mouse.
     */
    static void staticMotion(int x, int y);

    /**
     * @brief Static method to handle keyboard input.
     * @param key Key pressed.
     * @param x X position of the mouse.
     * @param y Y position of the mouse.
     */
    static void staticKeyboard(unsigned char key, int x, int y);

    /**
     * @brief Static method to handle key release.
     * @param key Key released.
     * @param x X position of the mouse.
     * @param y Y position of the mouse.
     */
    static void staticKeyboardUp(unsigned char key, int x, int y);

    /**
     * @brief Static method to handle special key input.
     * @param key Special key pressed.
     * @param x X position of the mouse.
     * @param y Y position of the mouse.
     */
    static void staticSpecial(int key, int x, int y);

    /**
     * @brief Initializes the 3D engine.
     */
    void init();

    /**
     * @brief Resets the cubes.
     */
    void resetCubes();

    /**
     * @brief Sets the coordinates for the cube.
     */
    void SetCubeCord();

    /**
     * @brief Draws all the figures.
     */
    void drawAllFigures();

    /**
     * @brief Saves the figures to a file.
     * @param filename Name of the file.
     */
    void saveFiguresToFile(const std::string& filename);

    /**
     * @brief Loads the figures from a file.
     * @param filename Name of the file.
     */
    void loadFiguresFromFile(const std::string& filename);

    /**
     * @brief Clears the file.
     * @param filename Name of the file.
     */
    void clearFile(const std::string& filename);

    /**
     * @brief Inputs RGB values.
     */
    void inputRGB();

    /**
     * @brief Quickly switches the color.
     */
    void QuickColorSwitch();

    /**
     * @brief Displays extra information.
     */
    void displayExtra();

    /**
     * @brief Displays the scene.
     */
    void display();

    /**
     * @brief Handles window reshape.
     * @param width New width of the window.
     * @param height New height of the window.
     */
    void reshape(int width, int height);

    /**
     * @brief Handles mouse input.
     * @param button Mouse button.
     * @param state State of the button.
     * @param x X position of the mouse.
     * @param y Y position of the mouse.
     */
    void mouse(int button, int state, int x, int y);

    /**
     * @brief Handles mouse motion.
     * @param x X position of the mouse.
     * @param y Y position of the mouse.
     */
    void motion(int x, int y);

    /**
     * @brief Handles keyboard input.
     * @param key Key pressed.
     * @param x X position of the mouse.
     * @param y Y position of the mouse.
     */
    void keyboard(unsigned char key, int x, int y);

    /**
     * @brief Handles key release.
     * @param key Key released.
     * @param x X position of the mouse.
     * @param y Y position of the mouse.
     */
    void keyboardUp(unsigned char key, int x, int y);

    /**
     * @brief Handles special key input.
     * @param key Special key pressed.
     * @param x X position of the mouse.
     * @param y Y position of the mouse.
     */
    void special(int key, int x, int y);

    /**
     * @brief Updates the camera.
     * @param value Integer value.
     */
    void updateCamera(int value);

    /**
     * @brief Checks for collisions with figures.
     * @param nextCameraPositionX Next camera position in X.
     * @param nextCameraPositionY Next camera position in Y.
     * @param nextCameraPositionZ Next camera position in Z.
     * @return True if there is a collision, false otherwise.
     */
    bool collisionWithFigures(GLfloat nextCameraPositionX, GLfloat nextCameraPositionY, GLfloat nextCameraPositionZ);

    /**
     * @brief Saves the date and time to a file.
     * @param filename Name of the file.
     * @param end_time End time.
     * @param elapsedTime Elapsed time.
     * @param StarCount Star count.
     */
    void saveDateTimeToFile(const std::string& filename, time_t end_time, float elapsedTime, int StarCount);

    /**
     * @brief Creates level 1 maze.
     */
    void CreateLvl1Maze();

    /**
     * @brief Creates level 2 maze.
     */
    void CreateLvl2Maze();

    /**
     * @brief Creates level 3 maze.
     */
    void CreateLvl3Maze();

    /**
     * @brief Checks if the camera crossed given boundaries.
     * @param granicaX1 Boundary X1.
     * @param granicaX2 Boundary X2.
     * @param granicaZ1 Boundary Z1.
     * @param granicaZ2 Boundary Z2.
     * @return True if crossed, false otherwise.
     */
    bool DidYouCross(float granicaX1, float granicaX2, float granicaZ1, float granicaZ2);

    /**
     * @brief Executes all triggers.
     */
    void AllTriggers();

    /**
     * @brief Checks if the elapsed time is longer than the given time.
     * @param start_time Start time.
     * @param end_time End time.
     * @param GivenTime Given time.
     * @return True if longer, false otherwise.
     */
    bool isLongerThanGivenTime(time_t start_time, time_t end_time, float GivenTime);

    /**
     * @brief Gets the current time.
     * @return Current time.
     */
    time_t getCurrentTime();

    /**
     * @brief Changes the frames per second.
     */
    void changeFPS();

    /**
     * @brief Runs the 3D engine.
     * @param argc Argument count.
     * @param argv Argument vector.
     */
    void run(int argc, char** argv);

    /**
     * @brief Initializes shadow mapping.
     */
    void initShadowMapping();

    /**
     * @brief Renders the scene from the light perspective.
     */
    void renderSceneFromLight();

    /**
     * @brief Draws the preview figure.
     */
    void drawPreviewFigure();

    /**
     * @brief Checks if a figure can be placed.
     * @return True if can place, false otherwise.
     */
    bool canPlaceFigure() const;

    /**
     * @brief Sets the frames per second.
     * @param fps Frames per second.
     */
    void setFPS(int fps);

    /**
     * @brief Shows the button map.
     */
    void showButtonMap();

    /**
     * @brief Prints the time results.
     */
    void printTimeResults();

    /**
     * @brief Handles mouse wheel input.
     * @param button Mouse button.
     * @param dir Direction.
     * @param x X position of the mouse.
     * @param y Y position of the mouse.
     */
    void mouseWheel(int button, int dir, int x, int y);

    /**
     * @brief Draws the menu background.
     */
    void drawMenuBackground();

    /**
     * @brief Renders text on the screen.
     * @param x X position.
     * @param y Y position.
     * @param font Font used.
     * @param text Text to render.
     */
    void renderText(float x, float y, void* font, const std::string& text);
};

#endif // ENGINE3D_H
