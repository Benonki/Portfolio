#include "Engine3D.h"

/**
 * @brief Constructs an Engine3D object and initializes default values.
 */
Engine3D::Engine3D()
    : cubeSize(2.0f), cameraDistance(5.0f), cameraAngleX(0.0f), cameraAngleY(0.0f),
    cameraPositionX(0.0f), cameraPositionY(0.0f), cameraPositionZ(0.0f),
    cubeX(0.0), cubeY(0.0), cubeZ(0.0), ColorR(1.0), ColorG(0.0), ColorB(0.0),
    isSpeedPressed(false), isMouseDragging(false), framePerSecond(1000 / 60),
    lastMouseX(0), lastMouseY(0), CurrQuickColor(0), cameraSpeed(1.5f), baseCameraSpeed(1.5f),
    showColoredEdges(false), shadingEnabled(true), AdminMode(true), CollisionMode(false),
    Level1Completed(false), Level2Completed(false), showExtra(true), TriggerUsed(false),
    WhUsed(false), startTime(0), endTime(0), TimeForTrigger(0), elapsedTime(0),
    rotationAngleX(0), rotationAngleY(0), MyFigure(new Figures()), selectedFigureType(0),
    isPlacingFigure(false), previewRotationX(0), previewRotationY(0), previewX(0), previewY(0),
    previewZ(0), selectedFPS(60), musicMuted(false), showMenu(false), menuSelection(0),
    scrollOffset(0), scrollIncrement(20), lightingEnabled(true), StarCounter(0)
{
    memset(keys, 0, sizeof(keys));

    if (!backgroundMusic.openFromFile("Popcorn.wav")) {
        std::cerr << "Error: Could not load music file." << std::endl;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(5);
}

/**
 * @brief Default destructor for Engine3D.
 */
Engine3D::~Engine3D() {
    backgroundMusic.stop();
    resetCubes();
    delete MyFigure;
}

/**
 * @brief Gets the singleton instance of the Engine3D.
 * @return Pointer to the singleton instance of Engine3D.
 */
Engine3D* Engine3D::getEngineInstance() {
    static Engine3D engineInstance;
    return &engineInstance;
}

/**
 * @brief Static callback for updating the camera.
 * @param value Integer value.
 */
void Engine3D::staticUpdateCamera(int value) {
    getEngineInstance()->updateCamera(value);
}

/**
 * @brief Static callback for display.
 */
void Engine3D::staticDisplay() {
    getEngineInstance()->display();
}

/**
 * @brief Static callback for special key input.
 * @param key Special key pressed.
 * @param x X position of the mouse.
 * @param y Y position of the mouse.
 */
void Engine3D::staticSpecial(int key, int x, int y) {
    getEngineInstance()->special(key, x, y);
}

/**
 * @brief Static callback for window reshape.
 * @param width New width of the window.
 * @param height New height of the window.
 */
void Engine3D::staticReshape(int width, int height) {
    getEngineInstance()->reshape(width, height);
}

/**
 * @brief Static callback for mouse input.
 * @param button Mouse button.
 * @param state State of the button.
 * @param x X position of the mouse.
 * @param y Y position of the mouse.
 */
void Engine3D::staticMouse(int button, int state, int x, int y) {
    getEngineInstance()->mouse(button, state, x, y);
}

/**
 * @brief Static callback for mouse motion.
 * @param x X position of the mouse.
 * @param y Y position of the mouse.
 */
void Engine3D::staticMotion(int x, int y) {
    getEngineInstance()->motion(x, y);
}

/**
 * @brief Static callback for keyboard input.
 * @param key Key pressed.
 * @param x X position of the mouse.
 * @param y Y position of the mouse.
 */
void Engine3D::staticKeyboard(unsigned char key, int x, int y) {
    getEngineInstance()->keyboard(key, x, y);
}

/**
 * @brief Static callback for key release.
 * @param key Key released.
 * @param x X position of the mouse.
 * @param y Y position of the mouse.
 */
void Engine3D::staticKeyboardUp(unsigned char key, int x, int y) {
    getEngineInstance()->keyboardUp(key, x, y);
}

/**
 * @brief Initializes the 3D engine, setting up OpenGL context and lighting.
 */
void Engine3D::init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }

    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    initShadowMapping();
}

/**
 * @brief Draws the background of the menu.
 */
void Engine3D::drawMenuBackground() {
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(glutGet(GLUT_WINDOW_WIDTH), 0);
    glVertex2f(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT));
    glEnd();
}

/**
 * @brief Resets the cubes to their initial state.
 */
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

/**
 * @brief Sets the coordinates for placing the cube.
 */
void Engine3D::SetCubeCord() {
    GLfloat distanceInFrontOfCamera = 5.0f;
    GLfloat dirX = sin(cameraAngleY * 3.14159265 / 180.0) * cos(cameraAngleX * 3.14159265 / 180.0);
    GLfloat dirY = sin(cameraAngleX * 3.14159265 / 180.0);
    GLfloat dirZ = cos(cameraAngleY * 3.14159265 / 180.0) * cos(cameraAngleX * 3.14159265 / 180.0);
    previewX = cameraPositionX + dirX * distanceInFrontOfCamera;
    previewY = cameraPositionY + dirY * distanceInFrontOfCamera;
    previewZ = cameraPositionZ + dirZ * distanceInFrontOfCamera;
}

/**
 * @brief Draws all figures in the scene.
 */
void Engine3D::drawAllFigures() {
    MyFigure->draw(showColoredEdges);
}

/**
 * @brief Saves the figures to a file.
 * @param filename Name of the file to save figures to.
 */
void Engine3D::saveFiguresToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& figure : MyFigure->getFigures()) {
            file << figure.x << " " << figure.y << " " << figure.z << " " << figure.cubeSize << " "
                << figure.r << " " << figure.g << " " << figure.b << " " << figure.rotationX << " " << figure.rotationY << " " << figure.rodzaj << "\n";
        }
        file.close();
        std::cout << "Zapisano konfiguracje figur do pliku: " << filename << std::endl;
    }
    else {
        std::cerr << "Nie mozna otworzyć pliku: " << filename << std::endl;
    }
}

/**
 * @brief Loads figures from a file.
 * @param filename Name of the file to load figures from.
 */
void Engine3D::loadFiguresFromFile(const std::string& filename) {
    resetCubes();
    AdminMode = false;
    CollisionMode = true;
    std::ifstream file(filename);
    if (file.is_open()) {
        GLfloat x, y, z, cubeSize, r, g, b, rotationX, rotationY;
        int rodzaj;
        while (file >> x >> y >> z >> cubeSize >> r >> g >> b >> rotationX >> rotationY >> rodzaj) {
            MyFigure->addFigure(x, y, z, cubeSize, r, g, b, rotationX, rotationY, rodzaj);
        }
        file.close();
        std::cout << "Wgrano konfiguracje figur z pliku: " << filename << std::endl;
        startTime = clock();
    }
    else {
        std::cerr << "Nie mozna otworzyć pliku: " << filename << std::endl;
    }
}

/**
 * @brief Clears the specified file.
 * @param filename Name of the file to clear.
 */
void Engine3D::clearFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file.clear();
        file.close();
        std::cout << "Wyczyszczono plik: " << filename << std::endl;
    }
    else {
        std::cerr << "Nie mozna otworzyć pliku: " << filename << std::endl;
    }
}

/**
 * @brief Inputs RGB values from the user.
 */
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

/**
 * @brief Switches the color quickly.
 */
void Engine3D::QuickColorSwitch() {
    if (CurrQuickColor == 0) {
        ColorR = 0;
        ColorG = 1;
        ColorB = 0;
        CurrQuickColor = 1;
    }
    else if (CurrQuickColor == 1) {
        ColorR = 0;
        ColorG = 0;
        ColorB = 1;
        CurrQuickColor = 2;
    }
    else if (CurrQuickColor == 2) {
        ColorR = 1;
        ColorG = 0;
        ColorB = 0;
        CurrQuickColor = 0;
    }
}

/**
 * @brief Handles special key input.
 * @param key Special key pressed.
 * @param x X position of the mouse.
 * @param y Y position of the mouse.
 */
void Engine3D::special(int key, int x, int y) {
    if (showMenu) {
        switch (key) {
        case GLUT_KEY_DOWN:
            menuSelection = (menuSelection < 2) ? menuSelection + 1 : 0;
            break;
        case GLUT_KEY_UP:
            menuSelection = (menuSelection > 0) ? menuSelection - 1 : 2;
            break;
        case GLUT_KEY_F1:
            if (menuSelection == 2) {
                exit(0);
            }
            break;
        }
        scrollOffset = 0;
        glutPostRedisplay();
        return;
    }
    switch (key) {
    case GLUT_KEY_UP:
        if (isPlacingFigure) previewRotationX -= 5.0f;
        break;
    case GLUT_KEY_DOWN:
        if (isPlacingFigure) previewRotationX += 5.0f;
        break;
    case GLUT_KEY_LEFT:
        if (isPlacingFigure) previewRotationY -= 5.0f;
        break;
    case GLUT_KEY_RIGHT:
        if (isPlacingFigure) previewRotationY += 5.0f;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

/**
 * @brief Shows the button map.
 */
void Engine3D::showButtonMap() {
    std::vector<std::string> buttonMap = {
    "w - Chodzenie do przodu",
    "a - Chodzenie do lewej",
    "s - Chodzenie do tylu",
    "d - Chodzenie do prawej",
    "f - Wlaczenie/Wylaczenie krawedzi",
    "l - Wlaczenie/Wylaczenie prostego cieniowania",
    "p - Wlaczenie/Wylaczenie oswietlenia"
    "x - Wlaczenie/Wylaczenie biegu",
    "m - Wlaczenie/Wylaczenie Labiryntu/Sandboxu",
    "i - Ukazanie informacji o statusach krawedzi, kolizji itd...",
    "z - Zmiana FPS'ow",
    "b - wyciszenie muzyki"
    "ESC - Menu",
    "------------------Tryb Sandbox:------------------",
    "SPACE - Ruch do gory",
    "LPM - obrot figury",
    "PPM - Zatwierdzenie figury",
    "Strzalka w Lewo - Obrot figury w Lewo",
    "Strzalka w Prawo - Obrot figury w Prawo",
    "Strzalka w Gore - Obrot figury w Gore",
    "Strzalka w Dol - Obrot figury w Dol",
    "c - Ruch w dol",
    "t - Zapisanie konfiguracji figur do pliku",
    "y - Wczytanie konfiguracji figur z pliku",
    "u - Wyczyszczenie pliku",
    "n - Cofniecie ostatniej figury",
    "0 - Zresetowanie Figur oraz pozycji kamery",
    "1 - Stworzenie szescianu",
    "2 - Stworzenie piramidy",
    "3 - Stworzenie sfery",
    "4 - Stworzenie gwiazdki",
    "5 - Stworzenie mety",
    "o - Wlaczenie/Wylaczenie kolizji",
    "k - Wpisanie nowego koloru RGB",
    "h - Wlaczenie/wylaczenie admina",
    "q - Szybka zmiana koloru RGB (czerwony -> zielony -> niebieski -> czerwony...)"
    };

    glColor3f(0.8, 0.8, 0.8);
    void* font = GLUT_BITMAP_HELVETICA_18;

    glRasterPos2f(300, glutGet(GLUT_WINDOW_HEIGHT) - 100 + scrollOffset);
    std::string header = "Mapa Przyciskow:";
    for (char c : header) {
        glutBitmapCharacter(font, c);
    }

    for (size_t i = 0; i < buttonMap.size(); ++i) {
        glRasterPos2f(300, glutGet(GLUT_WINDOW_HEIGHT) - (130 + i * 30) + scrollOffset);
        for (char c : buttonMap[i]) {
            glutBitmapCharacter(font, c);
        }
    }
}

/**
 * @brief Prints the time results.
 */
void Engine3D::printTimeResults() {
    std::ifstream file("Ranking.txt");
    if (file.is_open()) {
        std::string line;
        std::string dateTime;
        std::vector<std::pair<std::string, std::pair<std::string, int>>> results;

        while (std::getline(file, line)) {
            std::size_t foundEquals = line.find('=');
            std::size_t foundQuestion = line.find('?');
            std::size_t foundHash = line.find('#');
            if (foundEquals != std::string::npos && foundQuestion != std::string::npos && foundHash != std::string::npos) {
                std::string elapsedTime = line.substr(foundEquals + 1, foundQuestion - foundEquals - 1);
                std::string starCountStr = line.substr(foundQuestion + 1, foundHash - foundQuestion - 1);
                int starCount = std::stoi(starCountStr);
                results.push_back({ dateTime, { elapsedTime, starCount } });
            }
            else {
                std::stringstream ss(line);
                std::string token;
                if (std::getline(ss >> std::ws, token)) {
                    dateTime = token;
                }
            }
        }

        auto compareTimeResults = [](const std::pair<std::string, std::pair<std::string, int>>& a, const std::pair<std::string, std::pair<std::string, int>>& b) {
            double timeA = std::stod(a.second.first);
            double timeB = std::stod(b.second.first);
            return timeA < timeB;
            };

        std::sort(results.begin(), results.end(), compareTimeResults);

        glRasterPos2f(300, glutGet(GLUT_WINDOW_HEIGHT) - 130 + scrollOffset);
        std::string header = "Ranking Czasow:";
        for (char c : header) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }

        for (size_t i = 0; i < results.size(); ++i) {
            glRasterPos2f(300, glutGet(GLUT_WINDOW_HEIGHT) - (160 + i * 30) + scrollOffset);
            std::string result = std::to_string(i + 1) + ". Data: " + results[i].first + ", Wynik czasowy: " + results[i].second.first + ", Ilosc Gwiazdek: " + std::to_string(results[i].second.second);
            for (char c : result) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
            }
        }

        file.close();
    }
    else {
        glRasterPos2f(300, glutGet(GLUT_WINDOW_HEIGHT) - 130);
        std::string error = "Bląd: Nie można otworzyć pliku do odczytu.";
        for (char c : error) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }
}

/**
 * @brief Displays extra information on the screen.
 */
void Engine3D::displayExtra() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    if (AdminMode) {
        glColor3f(ColorR, ColorG, ColorB);
        std::string currentColorText = "Current Color: RGB";
        glRasterPos2f(glutGet(GLUT_WINDOW_WIDTH) - 160, 15);
        for (char c : currentColorText) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
        }
    }

    glColor3f(0.0f, 0.0f, 0.0f);
    if (!AdminMode) {
        endTime = clock();
        elapsedTime = static_cast<float>(endTime - startTime) / CLOCKS_PER_SEC;
        std::stringstream ss;
        ss << std::fixed << std::setprecision(3) << elapsedTime;
        std::string elapsedTimeText = "Time: " + ss.str() + " sec";
        glRasterPos2f(glutGet(GLUT_WINDOW_WIDTH) - 130, 15);
        for (char c : elapsedTimeText) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
        }
    }

    std::string cameraCoords = "X: " + std::to_string(cameraPositionX) + " Y: " + std::to_string(cameraPositionY) + " Z: " + std::to_string(cameraPositionZ);
    glRasterPos2f(10, glutGet(GLUT_WINDOW_HEIGHT) - 20);
    for (char c : cameraCoords) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
    }

    std::string fpsText = "FPS: " + std::to_string(selectedFPS);
    glRasterPos2f(glutGet(GLUT_WINDOW_WIDTH) - 80, glutGet(GLUT_WINDOW_HEIGHT) - 20);
    for (char c : fpsText) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
    }

    if (showExtra) {
        std::string speedStText = "Running: " + std::string(isSpeedPressed == true ? "YES" : "NO");
        glRasterPos2f(10, glutGet(GLUT_WINDOW_HEIGHT) - 50);
        for (char c : speedStText) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
        }

        std::string blockStText = "Collision: " + std::string(CollisionMode == true ? "YES" : "NO");
        glRasterPos2f(10, glutGet(GLUT_WINDOW_HEIGHT) - 70);
        for (char c : blockStText) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
        }

        std::string edgeStText = "Edges: " + std::string(showColoredEdges == true ? "YES" : "NO");
        glRasterPos2f(10, glutGet(GLUT_WINDOW_HEIGHT) - 90);
        for (char c : edgeStText) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
        }

        std::string lightingStText = "Lighting: " + std::string(lightingEnabled == true ? "YES" : "NO");
        glRasterPos2f(10, glutGet(GLUT_WINDOW_HEIGHT) - 110);
        for (char c : lightingStText) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
        }

        std::string shadowStText = "Shadows: " + std::string(shadingEnabled == true ? "YES" : "NO");
        glRasterPos2f(10, glutGet(GLUT_WINDOW_HEIGHT) - 130);
        for (char c : shadowStText) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
        }

        std::string AdminStText = "Admin: " + std::string(AdminMode == true ? "YES" : "NO");
        glRasterPos2f(10, glutGet(GLUT_WINDOW_HEIGHT) - 150);
        for (char c : AdminStText) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
        }
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    if (difftime(getCurrentTime(), messageStartTime) < 5) {
        renderText(10, 30, GLUT_BITMAP_HELVETICA_18, displayMessage);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    if (lightingEnabled) {
        glEnable(GL_LIGHTING);
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

/**
 * @brief Initializes shadow mapping.
 */
void Engine3D::initShadowMapping() {
    glGenFramebuffers(1, &depthMapFBO);

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/**
 * @brief Renders the scene from the light perspective.
 */
void Engine3D::renderSceneFromLight() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    drawAllFigures();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

/**
 * @brief Displays the scene.
 */
void Engine3D::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (showMenu) {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        drawMenuBackground();

        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);

        glColor3f(0.5, 0.5, 0.5);
        void* font = GLUT_BITMAP_HELVETICA_18;

        std::string menuOptions[] = { "Mapa Przyciskow", "Ranking Czasow", "Wyjscie" };
        for (int i = 0; i < 3; ++i) {
            if (i == menuSelection) {
                glColor3f(0.8, 0.0, 0.0);
            }
            else {
                glColor3f(0.2, 0.2, 0.2);
            }
            glRasterPos2f(100, glutGet(GLUT_WINDOW_HEIGHT) - (200 + i * 30));
            for (char c : menuOptions[i]) {
                glutBitmapCharacter(font, c);
            }
        }

        glColor3f(0.8, 0.8, 0.8);
        if (menuSelection == 2) {
            glRasterPos2f(300, glutGet(GLUT_WINDOW_HEIGHT) - 100);
            std::string text = "Potwierdz wyjscie naciskajac F1";
            for (char c : text) {
                glutBitmapCharacter(font, c);
            }
        }
        else if (menuSelection == 1) {
            printTimeResults();
        }
        else if (menuSelection == 0) {
            showButtonMap();
        }

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);

        glutSwapBuffers();
        return;
    }

    GLfloat dirX = sin(cameraAngleY * 3.14159265 / 180.0) * cos(cameraAngleX * 3.14159265 / 180.0);
    GLfloat dirY = sin(cameraAngleX * 3.14159265 / 180.0);
    GLfloat dirZ = cos(cameraAngleY * 3.14159265 / 180.0) * cos(cameraAngleX * 3.14159265 / 180.0);

    GLfloat upX = 0.0f;
    GLfloat upY = (cameraAngleX > 89.0f || cameraAngleX < -89.0f) ? 0.0f : 1.0f;
    GLfloat upZ = (cameraAngleX > 89.0f) ? -1.0f : ((cameraAngleX < -89.0f) ? 1.0f : 0.0f);

    gluLookAt(cameraPositionX, cameraPositionY, cameraPositionZ,
        cameraPositionX + dirX,
        cameraPositionY + dirY,
        cameraPositionZ + dirZ,
        upX, upY, upZ);

    GLfloat lightPosition[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

    drawAllFigures();
    if (isPlacingFigure) {
        SetCubeCord();
        drawPreviewFigure();
    }
    displayExtra();
    glutSwapBuffers();
}

/**
 * @brief Draws the preview figure.
 */
void Engine3D::drawPreviewFigure() {
    GLfloat mat_diffuse[] = { ColorR, ColorG, ColorB, 0.5 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColor4f(ColorR, ColorG, ColorB, 0.5);

    glPushMatrix();
    glTranslatef(previewX, previewY, previewZ);
    glRotatef(previewRotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(previewRotationY, 0.0f, 1.0f, 0.0f);

    if (selectedFigureType == 1) {
        MyFigure->drawCube(0, 0, 0, cubeSize, ColorR, ColorG, ColorB, 0, 0, showColoredEdges);
    }
    else if (selectedFigureType == 2) {
        MyFigure->drawTriangle(0, 0, 0, cubeSize, ColorR, ColorG, ColorB, 0, 0, showColoredEdges);
    }
    else if (selectedFigureType == 3) {
        MyFigure->drawSphere(0, 0, 0, cubeSize, ColorR, ColorG, ColorB, 0, 0, showColoredEdges);
    }
    else if (selectedFigureType == 4) {
        MyFigure->drawStar(0, 0, 0, cubeSize, ColorR, ColorG, ColorB, 0, 0, showColoredEdges);
    }
    else if (selectedFigureType == 5) {
        MyFigure->drawMeta(0, 0, 0, cubeSize, ColorR, ColorG, ColorB, 0, 0, showColoredEdges);
    }
    glPopMatrix();
}

/**
 * @brief Checks if a figure can be placed.
 * @return True if the figure can be placed, false otherwise.
 */
bool Engine3D::canPlaceFigure() const {
    return AdminMode;
}

/**
 * @brief Handles mouse motion.
 * @param x X position of the mouse.
 * @param y Y position of the mouse.
 */
void Engine3D::motion(int x, int y) {
    if (isMouseDragging) {
        float sensitivity = 0.3f;
        float deltaX = (x - lastMouseX) * sensitivity;
        float deltaY = (y - lastMouseY) * sensitivity;

        cameraAngleX -= deltaY;
        cameraAngleY -= deltaX;

        if (cameraAngleX > 89.0f) cameraAngleX = 89.0f;
        if (cameraAngleX < -89.0f) cameraAngleX = -89.0f;

        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

/**
 * @brief Handles keyboard input.
 * @param key Key pressed.
 * @param x X position of the mouse.
 * @param y Y position of the mouse.
 */
void Engine3D::keyboard(unsigned char key, int x, int y) {
    keys[key] = true;
    key = std::tolower(key);
    switch (key) {
    case '0':
        if (AdminMode) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            resetCubes();
        }
        break;
    case '1':
        if (AdminMode) {
            selectedFigureType = (selectedFigureType == 1) ? 0 : 1;
            isPlacingFigure = (selectedFigureType != 0);
            if (isPlacingFigure) {
                SetCubeCord();
                previewRotationX = 0.0f;
                previewRotationY = 0.0f;
            }
        }
        break;
    case '2':
        if (AdminMode) {
            selectedFigureType = (selectedFigureType == 2) ? 0 : 2;
            isPlacingFigure = (selectedFigureType != 0);
            if (isPlacingFigure) {
                SetCubeCord();
                previewRotationX = 0.0f;
                previewRotationY = 0.0f;
            }
        }
        break;
    case '3':
        if (AdminMode) {
            selectedFigureType = (selectedFigureType == 3) ? 0 : 3;
            isPlacingFigure = (selectedFigureType != 0);
            if (isPlacingFigure) {
                SetCubeCord();
                previewRotationX = 0.0f;
                previewRotationY = 0.0f;
            }
        }
        break;
    case '4':
        if (AdminMode) {
            selectedFigureType = (selectedFigureType == 4) ? 0 : 4;
            isPlacingFigure = (selectedFigureType != 0);
            if (isPlacingFigure) {
                SetCubeCord();
                previewRotationX = 0.0f;
                previewRotationY = 0.0f;
            }
        }
        break;
    case '5':
        if (AdminMode) {
            selectedFigureType = (selectedFigureType == 5) ? 0 : 5;
            isPlacingFigure = (selectedFigureType != 0);
            if (isPlacingFigure) {
                SetCubeCord();
                previewRotationX = 0.0f;
                previewRotationY = 0.0f;
            }
        }
        break;
    case 't':
        if (AdminMode) saveFiguresToFile("Maze.txt");
        break;
    case 'y':
        if (AdminMode) loadFiguresFromFile("Maze.txt");
        else if (!AdminMode) {
            endTime = clock();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            resetCubes();
            AdminMode = true;
        }
        break;
    case 'h':
        if (AdminMode) AdminMode = false;
        else AdminMode = true;
        break;
    case 'u':
        if (AdminMode) clearFile("Maze.txt");
        break;
    case 'f':
        showColoredEdges = !showColoredEdges;
        break;
    case 'o':
        if (AdminMode) CollisionMode = !CollisionMode;
        break;
    case 'z':
        changeFPS();
        break;
    case 'l':
        shadingEnabled = !shadingEnabled;
        if (shadingEnabled) {
            glShadeModel(GL_SMOOTH);
        }
        else {
            glShadeModel(GL_FLAT);
        }
        break;
    case 'k':
        if (AdminMode) inputRGB();
        break;
    case 'p':
        lightingEnabled = !lightingEnabled;
        if (lightingEnabled) {
            glEnable(GL_LIGHTING);
        }
        else {
            glDisable(GL_LIGHTING);
        }
    case 'q':
        if (AdminMode) QuickColorSwitch();
        break;
    case 'n':
        if (AdminMode) MyFigure->removeLastCube();
        break;
    case 'x':
        if (AdminMode) {
            isSpeedPressed = !isSpeedPressed;
            cameraSpeed = isSpeedPressed ? baseCameraSpeed * 2.5f : baseCameraSpeed;
        }
        break;
    case 'i':
        showExtra = !showExtra;
        break;
    case 'b':
        if (musicMuted) {
            backgroundMusic.play();
        }
        else {
            backgroundMusic.pause();
        }
        musicMuted = !musicMuted;
        break;
    case 'm':
        AdminMode = !AdminMode;
        if (!AdminMode) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            resetCubes();
            CollisionMode = true;
            showColoredEdges = true;
            showExtra = false;
            startTime = clock();
            CreateLvl1Maze();
            selectedFigureType = 0;
            isPlacingFigure = false;
            backgroundMusic.play();

        }
        else {
            endTime = clock();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            resetCubes();
            Level1Completed = false;
            Level2Completed = false;
            WhUsed = false;
            TriggerUsed = false;
            backgroundMusic.stop();

        }
        break;
    case 27:
        showMenu = !showMenu;
        break;
    default:
        break;
    }
}

/**
 * @brief Handles mouse input.
 * @param button Mouse button.
 * @param state State of the button.
 * @param x X position of the mouse.
 * @param y Y position of the mouse.
 */
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
    else if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN && isPlacingFigure && canPlaceFigure()) {
            MyFigure->addFigure(previewX, previewY, previewZ, cubeSize, ColorR, ColorG, ColorB, previewRotationX, previewRotationY, selectedFigureType);
            isPlacingFigure = false;
            selectedFigureType = 0;
            previewRotationX = 0.0f;
            previewRotationY = 0.0f;
        }
    }
    else if (showMenu && (button == 3 || button == 4)) {
        mouseWheel(button, (button == 3) ? 1 : -1, x, y);
    }
    else if (button == 3) {
        cubeSize += 0.1f;
    }
    else if (button == 4) {
        if (cubeSize > 0.1) cubeSize -= 0.1f;
    }
}

/**
 * @brief Handles mouse wheel input.
 * @param button Mouse button.
 * @param dir Direction.
 * @param x X position of the mouse.
 * @param y Y position of the mouse.
 */
void Engine3D::mouseWheel(int button, int dir, int x, int y) {
    if (showMenu && (menuSelection == 0 || menuSelection == 1)) {
        if (dir > 0) {
            scrollOffset -= scrollIncrement;
            if (scrollOffset < 0) scrollOffset = 0;
        }
        else {
            scrollOffset += scrollIncrement;
            if (scrollOffset > (300 + scrollIncrement * 40) - glutGet(GLUT_WINDOW_HEIGHT)) {
                scrollOffset = (300 + scrollIncrement * 40) - glutGet(GLUT_WINDOW_HEIGHT);
            }
        }
        glutPostRedisplay();
    }
}

/**
 * @brief Handles key release.
 * @param key Key released.
 * @param x X position of the mouse.
 * @param y Y position of the mouse.
 */
void Engine3D::keyboardUp(unsigned char key, int x, int y) {
    keys[key] = false;
}

/**
 * @brief Updates the camera.
 * @param value Integer value.
 */
void Engine3D::updateCamera(int value) {
    static clock_t lastTime = clock();
    clock_t currentTime = clock();
    float deltaTime = float(currentTime - lastTime) / CLOCKS_PER_SEC;
    lastTime = currentTime;

    cameraSpeed = baseCameraSpeed * deltaTime * (isSpeedPressed ? 3.5f : 1.0f);

    GLfloat nextCameraPositionX = cameraPositionX;
    GLfloat nextCameraPositionY = cameraPositionY;
    GLfloat nextCameraPositionZ = cameraPositionZ;

    if (keys['w'] || keys['W']) {
        nextCameraPositionX += cameraSpeed * sin(cameraAngleY * 3.14159265 / 180.0);
        nextCameraPositionZ += cameraSpeed * cos(cameraAngleY * 3.14159265 / 180.0);
    }
    if (keys['s'] || keys['S']) {
        nextCameraPositionX -= cameraSpeed * sin(cameraAngleY * 3.14159265 / 180.0);
        nextCameraPositionZ -= cameraSpeed * cos(cameraAngleY * 3.14159265 / 180.0);
    }
    if (keys['a'] || keys['A']) {
        nextCameraPositionX += cameraSpeed * cos(cameraAngleY * 3.14159265 / 180.0);
        nextCameraPositionZ -= cameraSpeed * sin(cameraAngleY * 3.14159265 / 180.0);
    }
    if (keys['d'] || keys['D']) {
        nextCameraPositionX -= cameraSpeed * cos(cameraAngleY * 3.14159265 / 180.0);
        nextCameraPositionZ += cameraSpeed * sin(cameraAngleY * 3.14159265 / 180.0);
    }
    if (keys[' '] && AdminMode) {
        nextCameraPositionY += cameraSpeed;
    }
    if ((keys['c'] || keys['C']) && AdminMode) {
        nextCameraPositionY -= cameraSpeed;
    }

    bool collision = collisionWithFigures(nextCameraPositionX, nextCameraPositionY, nextCameraPositionZ);
    if (!collision || !CollisionMode) {
        cameraPositionX = nextCameraPositionX;
        cameraPositionY = nextCameraPositionY;
        cameraPositionZ = nextCameraPositionZ;
    }
    else {
        GLfloat wallDirectionX = 0.0f, wallDirectionZ = 0.0f;
        if (nextCameraPositionX > cameraPositionX) {
            wallDirectionX = -1.0f;
        }
        else if (nextCameraPositionX < cameraPositionX) {
            wallDirectionX = 1.0f;
        }
        if (nextCameraPositionZ > cameraPositionZ) {
            wallDirectionZ = -1.0f;
        }
        else if (nextCameraPositionZ < cameraPositionZ) {
            wallDirectionZ = 1.0f;
        }
        GLfloat interpolationFactor = 0.1f;
        cameraPositionX = cameraPositionX + interpolationFactor * cameraSpeed * wallDirectionX;
        cameraPositionZ = cameraPositionZ + interpolationFactor * cameraSpeed * wallDirectionZ;
    }
    AllTriggers();
    glutTimerFunc(framePerSecond, staticUpdateCamera, 0);
    glutPostRedisplay();
}

/**
 * @brief Checks for collisions with figures.
 * @param nextCameraPositionX Next camera position in X.
 * @param nextCameraPositionY Next camera position in Y.
 * @param nextCameraPositionZ Next camera position in Z.
 * @return True if there is a collision, false otherwise.
 */
bool Engine3D::collisionWithFigures(GLfloat nextCameraPositionX, GLfloat nextCameraPositionY, GLfloat nextCameraPositionZ) {
    for (const auto& figure : MyFigure->getFigures()) {
        GLfloat cubeX = figure.x;
        GLfloat cubeY = figure.y;
        GLfloat cubeZ = figure.z;
        GLfloat cubeSize = figure.cubeSize;
        GLfloat margin = 0.1;
        if (nextCameraPositionX >= cubeX - (cubeSize / 2 + margin) && nextCameraPositionX <= cubeX + (cubeSize / 2 + margin) &&
            nextCameraPositionY >= cubeY - (cubeSize / 2 + margin) && nextCameraPositionY <= cubeY + (cubeSize / 2 + margin) &&
            nextCameraPositionZ >= cubeZ - (cubeSize / 2 + margin) && nextCameraPositionZ <= cubeZ + (cubeSize / 2 + margin)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Saves date and time to a file.
 * @param filename Name of the file.
 * @param end_time End time.
 * @param elapsedTime Elapsed time.
 * @param StarCount Number of stars.
 */
void Engine3D::saveDateTimeToFile(const std::string& filename, time_t end_time, float elapsedTime, int StarCount) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        char timeBuffer[26];
        struct tm timeInfo;
        localtime_s(&timeInfo, &end_time);
        asctime_s(timeBuffer, sizeof(timeBuffer), &timeInfo);
        file << timeBuffer;
        file << " = " << elapsedTime << " ? " << StarCount << " #" << std::endl;
        file.close();
    }
    else {
        std::cerr << "Błąd: Nie można otworzyć pliku do zapisu." << std::endl;
    }
}

/**
 * @brief Creates the level 1 maze.
 */
void Engine3D::CreateLvl1Maze() {
    const int mazeWidth = 9;
    const int mazeHeight = 9;
    int maze[mazeWidth][mazeHeight] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 1, 2, 0, 0, 0, 1},
        {1, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 1, 0, 0, 0, 1, 3, 0, 1},
        {1, 0, 0, 1, 1, 0, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 1},
        {1, 0, 0, 0, 1, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1},
    };
    int cubeSize = 1;
    srand(time(NULL));
    MyFigure->addFigure(2.87, 0, 8, cubeSize, ColorR, ColorG, ColorB, 0, 0, 5);
    for (int z = 0; z < mazeWidth; z++) {
        for (int x = 0; x < mazeHeight; x++) {
            float colorR = static_cast<float>(rand()) / RAND_MAX;
            float colorG = static_cast<float>(rand()) / RAND_MAX;
            float colorB = static_cast<float>(rand()) / RAND_MAX;
            if (maze[z][x] == 1) {
                MyFigure->addFigure(x - 4, 0, z - 1, cubeSize, colorR, colorG, colorB, 0, 0, 1);
            }
            if (maze[z][x] != 1) {
                MyFigure->addFigure(x - 4, -1, z - 1, cubeSize, colorR, colorG, colorB, 0, 0, 1);
            }
            if (maze[z][x] == 3) {
                MyFigure->addFigure(x - 4, 0, z - 1, 0.2, 1, 1, 0, 0, 0, 4);
            }
        }
    }
}

/**
 * @brief Creates the level 2 maze.
 */
void Engine3D::CreateLvl2Maze() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    resetCubes();
    Level1Completed = true;
    WhUsed = false;
    TriggerUsed = false;

    const int mazeWidth = 16;
    const int mazeHeight = 15;
    int maze[mazeWidth][mazeHeight] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 3, 1, 0, 1},
        {1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1},
        {1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1},
        {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1},
        {1, 1, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
    int cubeSize = 1;
    srand(time(NULL));
    MyFigure->addFigure(1.87, 0, -8, cubeSize, ColorR, ColorG, ColorB, 0, 0, 5);
    for (int z = 0; z < mazeWidth; z++) {
        for (int x = 0; x < mazeHeight; x++) {
            float colorR = static_cast<float>(rand()) / RAND_MAX;
            float colorG = static_cast<float>(rand()) / RAND_MAX;
            float colorB = static_cast<float>(rand()) / RAND_MAX;
            if (maze[z][x] == 1) {
                MyFigure->addFigure(x - 7, 0, z - 7, cubeSize, colorR, colorG, colorB, 0, 0, 1);
            }
            if (maze[z][x] != 1) {
                MyFigure->addFigure(x - 7, -1, z - 7, cubeSize, colorR, colorG, colorB, 0, 0, 1);
            }
            if (maze[z][x] == 3) {
                MyFigure->addFigure(x - 7, 0, z - 7, 0.2, 1, 1, 0, 0, 0, 4);
            }
        }
    }
}

/**
 * @brief Creates the level 3 maze.
 */
void Engine3D::CreateLvl3Maze() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    resetCubes();
    Level2Completed = true;
    WhUsed = false;
    TriggerUsed = false;

    const int mazeWidth = 21;
    const int mazeHeight = 21;
    int maze[mazeWidth][mazeHeight] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1 ,1},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0 ,0 ,1},
        {1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1 ,0 ,1},
        {1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0 ,0 ,1},
        {1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 2, 1, 1, 0, 1, 0, 1, 0, 1 ,0 ,1},
        {1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 ,0 ,1},
        {1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1 ,0 ,1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1 ,0 ,1},
        {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0 ,0 ,1},
        {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1 ,0 ,1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 ,1 ,1},
        {1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1 ,0 ,1},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 ,0 ,1},
        {1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1 ,0 ,1},
        {1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 ,0 ,1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1 ,0 ,1},
        {1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 ,0 ,1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1 ,1 ,1},
        {1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0 ,0 ,1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 3, 1, 0, 1, 0, 0, 0, 1 ,0 ,1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,0 ,1},
    };
    int cubeSize = 1;
    srand(time(NULL));
    MyFigure->addFigure(8.87, 0, 17, cubeSize, ColorR, ColorG, ColorB, 0, 0, 5);
    for (int z = 0; z < mazeWidth; z++) {
        for (int x = 0; x < mazeHeight; x++) {
            float colorR = static_cast<float>(rand()) / RAND_MAX;
            float colorG = static_cast<float>(rand()) / RAND_MAX;
            float colorB = static_cast<float>(rand()) / RAND_MAX;
            if (maze[z][x] == 1) {
                MyFigure->addFigure(x - 10, 0, z - 4, cubeSize, colorR, colorG, colorB, 0, 0, 1);
            }
            if (maze[z][x] != 1) {
                MyFigure->addFigure(x - 10, -1, z - 4, cubeSize, colorR, colorG, colorB, 0, 0, 1);
            }
            if (maze[z][x] == 3) {
                MyFigure->addFigure(x - 10, 0, z - 4, 0.2, 1, 1, 0, 0, 0, 4);
            }
        }
    }
}

/**
 * @brief Checks if the camera crossed a boundary.
 * @param granicaX1 Boundary X1.
 * @param granicaX2 Boundary X2.
 * @param granicaZ1 Boundary Z1.
 * @param granicaZ2 Boundary Z2.
 * @return True if crossed, false otherwise.
 */
bool Engine3D::DidYouCross(float granicaX1, float granicaX2, float granicaZ1, float granicaZ2) {
    return (cameraPositionX >= granicaX1 && cameraPositionX <= granicaX2 && cameraPositionZ >= granicaZ1 && cameraPositionZ <= granicaZ2);
}

/**
 * @brief Handles all triggers in the game.
 */
void Engine3D::AllTriggers() {
    time_t currentTime = getCurrentTime();
    if (!AdminMode && !Level1Completed && DidYouCross(2.5, 3.5, 6.35, 7)) {
        displayMessage = "Czas trwania przechodzenia 1 poziomu labiryntu: " + std::to_string(elapsedTime) + " sekundy.";
        messageStartTime = currentTime;
        CreateLvl2Maze();
    }
    if (!AdminMode && !Level1Completed && DidYouCross(2.45, 2.55, 1.4, 2.5) && !TriggerUsed) {
        MyFigure->removeFigureBySize(0.2);
        glDisable(GL_DEPTH_TEST);
        TimeForTrigger = currentTime;
        displayMessage = "Znajdzka na levelu 1 zostala znaleziona, otrzymujesz WH";
        messageStartTime = currentTime;
        StarCounter++;
        TriggerUsed = true;
    }
    if (!AdminMode && Level1Completed && DidYouCross(1.5, 2.5, (-6.55), (-6.35))) {
        WhUsed = false;
        TriggerUsed = false;
        displayMessage = "Czas trwania przechodzenia 2 poziomu labiryntu: " + std::to_string(elapsedTime) + " sekundy.";
        messageStartTime = currentTime;
        CreateLvl3Maze();
    }
    if (!AdminMode && Level1Completed && DidYouCross(3.5, 4.55, (-3.55), (-3.45)) && !TriggerUsed) {
        MyFigure->removeFigureBySize(0.2);
        glDisable(GL_DEPTH_TEST);
        TimeForTrigger = currentTime;
        displayMessage = "Znajdzka na levelu 2 została znaleziona, otrzymujesz WH";
        messageStartTime = currentTime;
        StarCounter++;
        TriggerUsed = true;
    }
    if (!AdminMode && Level2Completed && DidYouCross(8.5, 9.45, 16.25, 16.55)) {
        AdminMode = true;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        resetCubes();
        Level1Completed = false;
        Level2Completed = false;
        WhUsed = false;
        TriggerUsed = false;
        endTime = clock();
        elapsedTime = static_cast<float>(endTime - startTime) / CLOCKS_PER_SEC;
        displayMessage = "Czas trwania przechodzenia labiryntow " + std::to_string(elapsedTime) + " sekundy. Znalezione Gwiazdki: " + std::to_string(StarCounter);
        messageStartTime = currentTime;
        time_t end_time_t = time(nullptr);
        saveDateTimeToFile("Ranking.txt", end_time_t, elapsedTime, StarCounter);
    }
    if (!AdminMode && Level2Completed && DidYouCross(0.55, 1.45, 14.45, 14.55) && !TriggerUsed) {
        MyFigure->removeFigureBySize(0.2);
        glDisable(GL_DEPTH_TEST);
        TimeForTrigger = currentTime;
        displayMessage = "Znajdzka na levelu 3 zostala znaleziona, otrzymujesz WH";
        messageStartTime = currentTime;
        StarCounter++;
        TriggerUsed = true;
    }
    if (!AdminMode && isLongerThanGivenTime(TimeForTrigger, currentTime, (Level1Completed ? 4.0 : 2.0)) && TriggerUsed && !WhUsed) {
        glEnable(GL_DEPTH_TEST);
        WhUsed = true;
    }
}

/**
 * @brief Renders text on the screen.
 * @param x X position.
 * @param y Y position.
 * @param font Font to use.
 * @param text Text to render.
 */
void Engine3D::renderText(float x, float y, void* font, const std::string& text) {
    glColor3f(0.0f, 0.0f, 0.0f);
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx != 0 || dy != 0) {
                glRasterPos2f(x + dx, y + dy);
                for (const char& c : text) {
                    glutBitmapCharacter(font, c);
                }
            }
        }
    }
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);
    for (const char& c : text) {
        glutBitmapCharacter(font, c);
    }
}

/**
 * @brief Checks if the elapsed time is longer than a given time.
 * @param start_time Start time.
 * @param end_time End time.
 * @param GivenTime Given time.
 * @return True if longer, false otherwise.
 */
bool Engine3D::isLongerThanGivenTime(time_t start_time, time_t end_time, float GivenTime) {
    return difftime(end_time, start_time) > GivenTime;
}

/**
 * @brief Gets the current time.
 * @return Current time.
 */
time_t Engine3D::getCurrentTime() {
    return time(nullptr);
}

/**
 * @brief Sets the frames per second (FPS).
 * @param fps Frames per second.
 */
void Engine3D::setFPS(int fps) {
    selectedFPS = fps;
    if (fps == 30) {
        framePerSecond = 1000 / 30;
    }
    else if (fps == 60) {
        framePerSecond = 1000 / 60;
    }
    else if (fps == 144) {
        framePerSecond = 1000 / 144;
    }
    else {
        framePerSecond = 1000 / 60;
    }
}

/**
 * @brief Changes the FPS to the next setting.
 */
void Engine3D::changeFPS() {
    if (selectedFPS == 30) {
        setFPS(60);
    }
    else if (selectedFPS == 60) {
        setFPS(144);
    }
    else {
        setFPS(30);
    }
}

/**
 * @brief Handles window reshape.
 * @param width New width.
 * @param height New height.
 */
void Engine3D::reshape(int width, int height) {
    glutReshapeWindow(1000, 600);
    glViewport(0, 0, 1000, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1000.0f / 600.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

/**
 * @brief Runs the 3D engine.
 * @param argc Argument count.
 * @param argv Argument vector.
 */
void Engine3D::run(int argc, char** argv) {
    setlocale(LC_ALL, "polish");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(400, 200);
    glutCreateWindow("Labirynt 3D");
#ifdef _WIN32
    HWND hwnd = FindWindow(NULL, L"Labirynt 3D");
    if (hwnd != NULL) {
        long style = GetWindowLong(hwnd, GWL_STYLE);
        style &= ~WS_SIZEBOX;
        style &= ~WS_MAXIMIZEBOX;
        SetWindowLong(hwnd, GWL_STYLE, style);
    }
#endif
    init();
    glutDisplayFunc(staticDisplay);
    glutReshapeFunc(staticReshape);
    glutMouseFunc(staticMouse);
    glutMotionFunc(staticMotion);
    glutSpecialFunc(Engine3D::staticSpecial);
    glutKeyboardFunc(staticKeyboard);
    glutKeyboardUpFunc(staticKeyboardUp);
    glutTimerFunc(framePerSecond, staticUpdateCamera, 0);
    glutMainLoop();
}

