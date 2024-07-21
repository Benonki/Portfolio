#include "Gra w Statki.h"
#include "load.h"

int main() {
    srand((unsigned int)time(0)); //inicjalizacja generatora liczb pseudolosowych na podstawie aktualnego czasu
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gra w Statki", sf::Style::Titlebar | sf::Style::Close); //utworzenie okienka programu od rozmiarach WIDTH na HEIHT, posiadające pasek tytułowy i z brakiem możliwosci rozszerzenia okna i jego maksymalizacji, można jedynie zamknąć je

    window.setFramerateLimit(144); //ustawienie odświeżania okna na maksymalnie 144 klatek na sekundę
    window.setVerticalSyncEnabled(true); //ustawienie limitu klatek, odpowiednio do możliwości monitora


    if (!Load::loadGraphics()) { //wywołanie funkcji loadGraphics z jednoczesnym odniesieniem się do jej wyniku - w przypadku niepowiedzenia, zostanie wyświetlony odpowiedni komunikat
        std::cout << "Nie udalo sie wczytac plikow graficznych" << std::endl;
        return 1;
    }

    if (!Load::loadSounds()) { //wywołanie funkcji loadSounds z jednoczesnym odniesieniem się do jej wyniku - w przypadku niepowiedzenia, zostanie wyświetlony odpowiedni komunikat
        std::cout << "Nie udalo sie wczytac plikow dzwiekowych" << std::endl;
        return 1;
    }

    backgroundMusic.setVolume(1); //ustawienie głośności muzyki w tle na 1
    backgroundMusic.setLoop(true); //włączenie "loopowania" muzyki tła
    backgroundMusic.play(); //włączenie muzyki

    sf::Sprite backgroundSprite(backgroundTexture); //przypisanie obiektowi "backgroundSprite" tektury tła menu; Sprite umożliwia wyświetlanie grafiki w oknie (jako tło)
    sf::Sprite backgroundSprite1(backgroundTexture1); //przypisanie obiektowi "backgroundSprite1" tektury tła rozgrywki; Sprite umożliwia wyświetlanie grafiki w oknie (jako tło)

    //////////////////////////////////////////////////////// tworzenie obiektów do menu

    sf::RectangleShape button1(sf::Vector2f(249, 79)); //utworzenie obiektu, odpowiadającego za przycisk "start" i przypisanie mu odpowiednich wartości wraz z teksturą
    button1.setPosition(sf::Vector2f(808, 174));
    button1.setTexture(&start);

    sf::RectangleShape button2(sf::Vector2f(249, 79)); //utworzenie obiektu, odpowiadającego za przycisk "tryb" i przypisanie mu odpowiednich wartości wraz z teksturą
    button2.setPosition(sf::Vector2f(808, 262));
    button2.setTexture(&tryb);

    sf::RectangleShape button3(sf::Vector2f(249, 79)); //utworzenie obiektu, odpowiadającego za przycisk "wyjdz" i przypisanie mu odpowiednich wartości wraz z teksturą
    button3.setPosition(sf::Vector2f(808, 350));
    button3.setTexture(&wyjdz);

    sf::RectangleShape button4(sf::Vector2f(249, 79)); //utworzenie obiektu, odpowiadającego za przycisk "Gracz vs Gracz" i przypisanie mu odpowiednich wartości wraz z teksturą
    button4.setPosition(sf::Vector2f(808, 174));
    button4.setTexture(&graczvsgracz);

    sf::RectangleShape button5(sf::Vector2f(249, 79)); //utworzenie obiektu, odpowiadającego za przycisk "Gracz vs Ai" i przypisanie mu odpowiednich wartości wraz z teksturą
    button5.setPosition(sf::Vector2f(808, 262));
    button5.setTexture(&graczvsai);

    sf::RectangleShape button6(sf::Vector2f(249, 79)); //utworzenie obiektu, odpowiadającego za przycisk "Bomby" i przypisanie mu odpowiednich wartości wraz z teksturą
    button6.setPosition(sf::Vector2f(808, 350));
    button6.setTexture(&bomby);

    sf::RectangleShape button7(sf::Vector2f(249, 79)); //utworzenie obiektu, odpowiadającego za przycisk "Bez bomb" i przypisanie mu odpowiednich wartości wraz z teksturą
    button7.setPosition(sf::Vector2f(808, 438));
    button7.setTexture(&bezbomb);

    sf::RectangleShape button8(sf::Vector2f(68, 77)); //utworzenie obiektu, odpowiadającego za przycisk włączający i wyłączający muzykę w menu i przypisanie mu odpowiednich wartości wraz z teksturą
    button8.setPosition(sf::Vector2f(18, 18));
    button8.setTexture(&music);

    sf::RectangleShape obiekt13(sf::Vector2f(86, 18)); //utworzenie obiektu, odpowiadającego za wyświetlanie wersji gry i przypisanie mu odpowiednich wartości wraz z teksturą
    obiekt13.setPosition(sf::Vector2f(11, 573));
    obiekt13.setTexture(&wersja);

    //////////////////////////////////////////////////////// tworzenie obiektów potrzebnych podczas rozgrywki

    sf::RectangleShape button9(sf::Vector2f(37, 37)); //utworzenie obiektu, odpowiadającego za przycisk wyjscia do menu podczas rozgrywki i przypisanie mu odpowiednich wartości wraz z teksturą
    button9.setPosition(sf::Vector2f(1113, 0));
    button9.setTexture(&wyjscietlo);

    sf::RectangleShape obiekt1(sf::Vector2f(271, 51)); //utworzenie obiektu, odpowiadającego za napis "Twoja Kolej" i przypisanie mu odpowiednich wartości wraz z teksturą
    obiekt1.setPosition(sf::Vector2f(442, 557));
    obiekt1.setTexture(&twojakolej);

    sf::RectangleShape obiekt4(sf::Vector2f(250, 52)); //utworzenie obiektu, odpowiadającego za napis "Plansza Gracza" i przypisanie mu odpowiednich wartości wraz z teksturą
    obiekt4.setPosition(sf::Vector2f(170, 0));
    obiekt4.setTexture(&planszagracza);

    sf::RectangleShape obiekt5(sf::Vector2f(307, 53)); //utworzenie obiektu, odpowiadającego za napis "Plansza Gracza nr1" i przypisanie mu odpowiednich wartości wraz z teksturą
    obiekt5.setPosition(sf::Vector2f(146, 0));
    obiekt5.setTexture(&planszagracza1);

    sf::RectangleShape obiekt6(sf::Vector2f(313, 53)); //utworzenie obiektu, odpowiadającego za napis "Plansza Gracza nr2" i przypisanie mu odpowiednich wartości wraz z teksturą
    obiekt6.setPosition(sf::Vector2f(694, 0));
    obiekt6.setTexture(&planszagracza2);

    sf::RectangleShape obiekt8(sf::Vector2f(516, 265)); //utworzenie obiektu, odpowiadającego za napis "Gracz rozstawia statki" i przypisanie mu odpowiednich wartości wraz z teksturą
    obiekt8.setPosition(sf::Vector2f(592, 169));
    obiekt8.setTexture(&wygenGracz);

    sf::RectangleShape obiekt9(sf::Vector2f(516, 265)); //utworzenie obiektu, odpowiadającego za napis "Gracz nr1 rozstawia statki" i przypisanie mu odpowiednich wartości wraz z teksturą
    obiekt9.setPosition(sf::Vector2f(592, 169));
    obiekt9.setTexture(&wygenGracznr1);

    sf::RectangleShape obiekt10(sf::Vector2f(516, 265)); //utworzenie obiektu, odpowiadającego za napis "Gracz nr2 rozstawia statki" i przypisanie mu odpowiednich wartości wraz z teksturą
    obiekt10.setPosition(sf::Vector2f(44, 169));
    obiekt10.setTexture(&wygenGracznr2);

    sf::RectangleShape obiekt11(sf::Vector2f(303, 52)); //utworzenie obiektu, odpowiadającego za napis "Plansza Komputera" i przypisanie mu odpowiednich wartości wraz z teksturą
    obiekt11.setPosition(sf::Vector2f(700, 0));
    obiekt11.setTexture(&planszakomputera);

    sf::RectangleShape button8a(sf::Vector2f(32, 36)); //utworzenie obiektu, odpowiadającego za przycisk włączający i wyłączający muzykę podczas rozgrywki i przypisanie mu odpowiednich wartości wraz z teksturą
    button8a.setPosition(sf::Vector2f(3, 3));
    button8a.setTexture(&music4);

    sf::RectangleShape obiekt12(sf::Vector2f(1150, 600)); //utworzenie obiektu, odpowiadającego za grafikę zakończenia rozgrywki i przypisanie mu odpowiednich wartości (tektura zostanie dopasowana do wyniku w dalszej części kodu
    obiekt12.setPosition(sf::Vector2f(0, 0));

    ////////////////////////////////////////////////////////

    sf::Cursor cursor; //utworzenie obiektu, odpowiadającego za kursor i przypisanie mu odpowiednich wartości wraz z teksturą
    cursor.loadFromPixels(cursorTexture.copyToImage().getPixelsPtr(), cursorTexture.getSize(), { 0, 0 });
    window.setMouseCursor(cursor); //zmodyfikowany kursor tylko w zakresie okna

    bool isButton1Hovered = false; //zmienna informująca czy podświetlić przycisk start czy nie
    bool isButton2Hovered = false; //zmienna informująca czy podświetlić przycisk tryb czy nie
    bool isButton3Hovered = false; //zmienna informująca czy podświetlić przycisk wyjdz czy nie
    bool isButton4Hovered = false; //zmienna informująca czy podświetlić przycisk czy nie
    bool isButton5Hovered = false; //zmienna informująca czy podświetlić przycisk czy nie
    bool isButton6Hovered = false; //zmienna informująca czy podświetlić przycisk czy nie
    bool isButton7Hovered = false; //zmienna informująca czy podświetlić przycisk czy nie
    bool isButton8Hovered = false; //zmienna informująca czy podświetlić przycisk czy nie
    bool isButton8aHovered = false; //zmienna informująca czy podświetlić przycisk odpowiadający za włączenie/wyłączenie muzyki czy nie
    bool isButton9Hovered = false; //zmienna informująca czy podświetlić przycisk czy nie
    bool musicOn = true; //zmienna informująca czy ma być odtwarzana muzyka w tle czy nie (dokładnie wyciszona)
    bool graczVSgracz = false; //zmienna informująca czy wybrano tryb Gracz vs Gracz, podstawowo jest Gracz vs Ai
    bool czyBomba = false; //zmienna informująca czy wybrano tryb z bombami, podstawowo jest bez bomb

    while (window.isOpen()) //gdy okno jest otwarte ma być wykonywany kod zawarty w tym while
    {

        sf::Event event; //utowrzenie zmiennej event, która będzie odpowiadać za wykrywanie przesunięcia myszki oraz kliknięcia
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) //jeżeli użytkownik próbuje zamknąć okno to wywołujemy window.close() - zamykamy okno
                window.close();

            cursorTexture.loadFromFile("grafika/kursorStatki48_1.png"); //załadowanie kursora myszki - konkretnie wersji zielonej. Po rozgrywce, jeżeli była ustawiona tekstura wersji czerwonej, to umieszczenie tutaj tego kodu umożliwia po powrocie z menu przywrócić jej zielony kolor
            cursor.loadFromPixels(cursorTexture.copyToImage().getPixelsPtr(), cursorTexture.getSize(), { 0, 0 });
            window.setMouseCursor(cursor);

            if (event.type == sf::Event::MouseMoved) //jeżeli wykryto ruch myszką
            {
                
                if (button1.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk start
                {
                    if (!isButton1Hovered) //jezeli nie był "podświetlony", to go "podświetla"
                    {
                        isButton1Hovered = true;
                        button1.setTexture(&start1);
                        placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                    }
                }
                else //jeżeli kursora nie ma na przycisku
                {
                    if (isButton1Hovered) //jeżeli jest "podświetlony", to przywraca podstawową tekturę
                    {
                        isButton1Hovered = false;
                        button1.setTexture(&start);
                    }
                }

                if (button2.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk tryb
                {
                    if (!isButton2Hovered) //jezeli nie był "podświetlony", to go "podświetla"
                    {
                        isButton2Hovered = true;
                        button2.setTexture(&tryb1);
                        placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                    }
                }
                else //jeżeli kursora nie ma na przycisku
                {
                    if (isButton2Hovered) //jeżeli jest "podświetlony", to przywraca podstawową tekturę
                    {
                        isButton2Hovered = false;
                        button2.setTexture(&tryb);
                    }
                }

                if (button3.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk wyjdz
                {
                    if (!isButton3Hovered) //jezeli nie był "podświetlony", to go "podświetla"
                    {
                        isButton3Hovered = true;
                        button3.setTexture(&wyjdz1);
                        placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                    }
                }
                else //jeżeli kursora nie ma na przycisku
                {
                    if (isButton3Hovered) //jeżeli jest "podświetlony", to przywraca podstawową tekturę
                    {
                        isButton3Hovered = false;
                        button3.setTexture(&wyjdz);
                    }
                }

                if (button8.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk włączający i wyłączający muzykę w menu
                {
                    if (musicOn) {
                        if (!isButton8Hovered) //jezeli nie był "podświetlony" i muzyka nie jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                        {
                            isButton8Hovered = true;
                            button8.setTexture(&music1);
                            placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                        }
                    }
                    else {
                        if (!isButton8Hovered) //jezeli nie był "podświetlony" i muzyka jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                        {
                            isButton8Hovered = true;
                            button8.setTexture(&music2b);
                            placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                        }
                    }

                }
                else //jeżeli kursora nie ma na przycisku
                {
                    if (musicOn) {
                        if (isButton8Hovered) //jezeli był "podświetlony" i muzyka nie jest wyciszona, to przywraca odpowiednio podstawową tekturę
                        {
                            isButton8Hovered = false;
                            button8.setTexture(&music);
                        }
                    }
                    else {
                        if (isButton8Hovered) //jezeli był "podświetlony" i muzyka jest wyciszona, to przywraca odpowiednio podstawową tekturę
                        {
                            isButton8Hovered = false;
                            button8.setTexture(&music2);
                        }
                    }
                }
            }

            window.clear(); //wyczyszczenie okna
            window.draw(backgroundSprite); //"utworzenie" grafiki tła
            window.draw(button1); //"utworzenie" przycisku start
            window.draw(button2); //"utworzenie" przycisku tryb
            window.draw(button3); //"utworzenie" przycisku wyjdź
            window.draw(button8); //"utworzenie" przycisku włączającego i wyłączającego muzykę
            window.draw(obiekt13); //"utworzenie" obiektu odpowiadającego za wyświetlanie wersji gry
            window.display(); //wyświetlenie utworzonych obiektów

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) //gdy naciśnięto lewy przycisk myszki
            {
                if (button1.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli naciśnięto przycisk start - gra zostaje rozpoczęta
                {
                    if (!graczVSgracz) { //sprawdzenie jaki tryb mamy, jeżeli graczVSgracz == false, to tryb gry to Gracz vs Ai

                        // Rozpoczęcie gry
                        Board playerBoard(50, 50, SQUARE_SIZE); //utworzenie planszy gracza
                        Board aiBoard(600, 50, SQUARE_SIZE); //utworzenie planszy komputera
                        bool czyWyjsc2 = false; //zmienna boolowska informująca czy mamy wyjść z pętli i wrócić do menu

                        //rozłożenie statków gracza
                        int numShips = 10; //10 statków
                        while (numShips > 0) {
                            Event event;
                            while (window.pollEvent(event)) { //rejestrowanie zdarzeń
                                if (event.type == Event::Closed) {
                                    window.close();
                                    return 0;
                                }
                                if (event.type == sf::Event::MouseMoved) { //gdy kursor się poruszył

                                    if (button9.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk odpowiadający za wyjście do menu
                                    {
                                        if (!isButton9Hovered) //jezeli nie był "podświetlony", to go "podświetla"
                                        {
                                            isButton9Hovered = true;
                                            button9.setTexture(&wyjscietlo1);
                                            placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                        }
                                    }
                                    else //jeżeli kursora nie ma na przycisku
                                    {
                                        if (isButton9Hovered) //jeżeli jest "podświetlony", to przywraca podstawową tekturę
                                        {
                                            isButton9Hovered = false;
                                            button9.setTexture(&wyjscietlo);
                                        }
                                    }
                                    if (button8a.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk włączający i wyłączający muzykę podczas rozgrywki
                                    {
                                        if (musicOn) {
                                            if (!isButton8aHovered) //jezeli nie był "podświetlony" i muzyka nie jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                            {
                                                isButton8aHovered = true;
                                                button8a.setTexture(&music4b);
                                                placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                            }
                                        }
                                        else {
                                            if (!isButton8aHovered) //jezeli nie był "podświetlony" i muzyka jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                            {
                                                isButton8aHovered = true;
                                                button8a.setTexture(&music5b);
                                                placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                            }
                                        }

                                    }
                                    else //jeżeli kursora nie ma na przycisku
                                    {
                                        if (musicOn) {
                                            if (isButton8aHovered) //jezeli był "podświetlony" i muzyka nie jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                            {
                                                isButton8aHovered = false;
                                                button8a.setTexture(&music4);
                                            }
                                        }
                                        else {
                                            if (isButton8aHovered) //jezeli był "podświetlony" i muzyka jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                            {
                                                isButton8aHovered = false;
                                                button8a.setTexture(&music5);
                                            }
                                        }
                                    }
                                    //inicjalizacja zmiennych potrzebnych do określenia czy kursor znajduje się nad planszą gracza
                                    int x = event.mouseMove.x - playerBoard.m_x;
                                    int y = event.mouseMove.y - playerBoard.m_y;
                                    int row = y / SQUARE_SIZE;
                                    int col = x / SQUARE_SIZE;

                                    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && playerBoard.m_cells[row][col] == CellState::Empty) { //sprawdzenie, czy kursor znajduje się na planszy gracza
                                        playerBoard.m_highlightedRow = row;  //ustawienie wiersza podświetlanego pola
                                        playerBoard.m_highlightedCol = col;  //ustawienie kolumny podświetlanego pola
                                    }
                                    else {
                                        playerBoard.m_highlightedRow = -1;  //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola
                                        playerBoard.m_highlightedCol = -1;  //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola
                                    }
                                }
                                else {
                                    playerBoard.m_highlightedRow = -1;  //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola (ta linia uniemożliwia zostawienie "niepotrzebnie podświetlonego pola" poza zakończeniu konretnych etapów rozgrywki)
                                    playerBoard.m_highlightedCol = -1;  //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola (ta linia uniemożliwia zostawienie "niepotrzebnie podświetlonego pola" poza zakończeniu konretnych etapów rozgrywki)
                                }

                                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) //jeżeli kliknięto lewy przycisk myszki
                                {
                                    if (button9.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk wyjścia do menu podczas rozgrywki
                                    {
                                        czyWyjsc2 = true; //wyjście do menu
                                    }
                                    else if (button8a.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk włączający i wyłączający muzykę podczas rozgrywki
                                    {
                                        if (musicOn) //wyciszamy muzykę i ustawiamy odpowiednią teksturę
                                        {
                                            button8a.setTexture(&music5);
                                            musicOn = false;
                                            backgroundMusic.setVolume(0);
                                        }
                                        else { //jeżeli była już wyciszona to ją odciszamy i przywracamy odpowiednią teksturę
                                            button8a.setTexture(&music4);
                                            musicOn = true;
                                            backgroundMusic.setVolume(1);
                                        }
                                    }
                                }

                                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) { //ustawianie statków, sprawdzanie czy i które pole na planszy kliknięto i wywołanie funkcji placeShip() dla playerBoard
                                    int x = event.mouseButton.x - playerBoard.m_x;
                                    int y = event.mouseButton.y - playerBoard.m_y;
                                    if (x > 0 && x < playerBoard.m_squareSize * COLS && y > 0 && y < playerBoard.m_squareSize * ROWS) {
                                        int row = y / SQUARE_SIZE;
                                        int col = x / SQUARE_SIZE;
                                        if (playerBoard.placeShip(row, col)) {
                                            numShips--;
                                            placeShipSound.play();
                                        }
                                    }
                                }
                            }
                            if (czyWyjsc2) //jeżeli prawda to wychodzimy z pętli
                            {
                                break;
                            }

                            //"rysowanie" i wyświetlanie obiektów
                            window.clear();
                            window.draw(backgroundSprite1);
                            playerBoard.draw(window, 0); //plansza gracza
                            window.draw(obiekt4);
                            window.draw(obiekt11);
                            window.draw(obiekt8);
                            window.draw(button9);
                            window.draw(button8a);
                            window.display();

                        }
                        if (czyWyjsc2) //jeżeli prawda to "wychodzimy do menu"
                        {
                            break;
                        }

                        //rozłożenie statków komputera
                        numShips = 10;
                        while (numShips > 0) {
                            int row = rand() % ROWS;
                            int col = rand() % COLS;
                            if (aiBoard.placeShip(row, col)) { //wywołanie funkcji sprawdzającej i ustawiającej status pola, jeżeli true, to udało się umieścić statek
                                numShips--;
                            }
                        }

                        //rozłożenie bomb na planszy gracza (3 bomby)
                        if (czyBomba) {
                            int bomby = 3;
                            while (bomby > 0) {
                                int row = rand() % ROWS;
                                int col = rand() % COLS;
                                if (playerBoard.m_cells[row][col] == CellState::Empty) { //sprawdza czy pole jest "puste"

                                    if (playerBoard.placeBomb(row, col)) {
                                        bomby--;
                                    }
                                }
                            }
                        }

                        //rozłożenie bomb na planszy komputera (3 bomby)
                        if (czyBomba) {
                            int bomby = 3;
                            while (bomby > 0) {
                                int row = rand() % ROWS;
                                int col = rand() % COLS;
                                if (aiBoard.m_cells[row][col] == CellState::Empty) { //sprawdza czy pole jest "puste"

                                    if (aiBoard.placeBomb(row, col)) {
                                        bomby--;
                                    }
                                }
                            }
                        }
                        //"rysowanie" i wyświetlanie obiektów
                        window.clear();
                        window.draw(backgroundSprite1);
                        playerBoard.draw(window, 0);
                        window.draw(obiekt4);
                        window.draw(obiekt11);
                        window.draw(obiekt8);
                        window.draw(button9);
                        window.draw(button8a);
                        window.display();

                        //część kodu i pętla fazy prób strzelania w statki
                        bool playerTurn = true; //zaczyna gracz
                        bool czyWyjsc = false; //zmienna do wyjścia do menu

                        while (window.isOpen() && czyWyjsc == false) { //gdy okno jest otwarte i nie wychodzimy do menu
                            Event event;
                            while (window.pollEvent(event)) { //rejestrowanie zdarzeń
                                if (event.type == Event::Closed) {
                                    window.close();
                                    return 0;
                                }

                                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) //jeżeli kliknięto lewy przycisk myszki
                                {
                                    if (button9.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk wyjścia do menu podczas rozgrywki
                                    {
                                        czyWyjsc2 = true; //wyjście do menu
                                    }
                                    else if (button8a.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk włączający i wyłączający muzykę podczas rozgrywki
                                    {
                                        if (musicOn) //wyciszamy muzykę i ustawiamy odpowiednią teksturę
                                        {
                                            button8a.setTexture(&music5);
                                            musicOn = false;
                                            backgroundMusic.setVolume(0);
                                        }
                                        else { //jeżeli była już wyciszona to ją odciszamy i przywracamy odpowiednią teksturę
                                            button8a.setTexture(&music4);
                                            musicOn = true;
                                            backgroundMusic.setVolume(1);
                                        }
                                    }
                                }

                                if (event.type == sf::Event::MouseMoved) { //gdy kursor się poruszył

                                    if (button9.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk odpowiadający za wyjście do menu
                                    {
                                        if (!isButton9Hovered) //jezeli nie był "podświetlony", to go "podświetla"
                                        {
                                            isButton9Hovered = true;
                                            button9.setTexture(&wyjscietlo1);
                                            placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                        }
                                    }
                                    else //jeżeli kursora nie ma na przycisku
                                    {
                                        if (isButton9Hovered) //jeżeli jest "podświetlony", to przywraca podstawową tekturę
                                        {
                                            isButton9Hovered = false;
                                            button9.setTexture(&wyjscietlo);
                                        }
                                    }
                                    if (button8a.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk włączający i wyłączający muzykę podczas rozgrywki
                                    {
                                        if (musicOn) {
                                            if (!isButton8aHovered) //jezeli nie był "podświetlony" i muzyka nie jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                            {
                                                isButton8aHovered = true;
                                                button8a.setTexture(&music4b);
                                                placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                            }
                                        }
                                        else {
                                            if (!isButton8aHovered) //jezeli nie był "podświetlony" i muzyka jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                            {
                                                isButton8aHovered = true;
                                                button8a.setTexture(&music5b);
                                                placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                            }
                                        }

                                    }
                                    else //jeżeli kursora nie ma na przycisku
                                    {
                                        if (musicOn) {
                                            if (isButton8aHovered) //jezeli był "podświetlony" i muzyka nie jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                            {
                                                isButton8aHovered = false;
                                                button8a.setTexture(&music4);
                                            }
                                        }
                                        else {
                                            if (isButton8aHovered) //jezeli był "podświetlony" i muzyka jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                            {
                                                isButton8aHovered = false;
                                                button8a.setTexture(&music5);
                                            }
                                        }
                                    }

                                    //inicjalizacja zmiennych potrzebnych do określenia czy kursor znajduje się nad planszą komputera
                                    int x = event.mouseMove.x - aiBoard.m_x;
                                    int y = event.mouseMove.y - aiBoard.m_y;
                                    int row = y / SQUARE_SIZE;
                                    int col = x / SQUARE_SIZE;

                                    if (x > 0 && x < aiBoard.m_squareSize * COLS && y > 0 && y < aiBoard.m_squareSize * ROWS && (aiBoard.m_cells[row][col] == CellState::Empty || aiBoard.m_cells[row][col] == CellState::Ship || aiBoard.m_cells[row][col] == CellState::Bomb)) {  //sprawdzenie, czy kursor znajduje się na planszy komputera i na określonym statusie pola
                                        aiBoard.m_highlightedRow = row;  //ustawienie wiersza podświetlanego pola
                                        aiBoard.m_highlightedCol = col;  //ustawienie kolumny podświetlanego pola
                                    }
                                    else {
                                        aiBoard.m_highlightedRow = -1; //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola
                                        aiBoard.m_highlightedCol = -1; //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola
                                    }
                                }
                                else {
                                    aiBoard.m_highlightedRow = -1; //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola (ta linia uniemożliwia zostawienie "niepotrzebnie podświetlonego pola" poza zakończeniu konretnych etapów rozgrywki)
                                    aiBoard.m_highlightedCol = -1; //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola (ta linia uniemożliwia zostawienie "niepotrzebnie podświetlonego pola" poza zakończeniu konretnych etapów rozgrywki)
                                }

                                if (playerTurn) { //gdy jest kolej gracza
                                    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) { //gdy kliknięto lewy przycisk myszki
                                        int x = event.mouseButton.x - aiBoard.m_x; //przypisanie położenia
                                        int y = event.mouseButton.y - aiBoard.m_y; //przypisanie położenia
                                        if (x > 0 && x < aiBoard.m_squareSize * COLS && y > 0 && y < aiBoard.m_squareSize * ROWS) { //jeżeli zalicza tylko kliknięcia w obszarze planszy komputera
                                            int row = y / SQUARE_SIZE;
                                            int col = x / SQUARE_SIZE;
                                            if (aiBoard.m_cells[row][col] == CellState::Hit || aiBoard.m_cells[row][col] == CellState::Miss || aiBoard.m_cells[row][col] == CellState::hitBomb) { //nie zalicza ruchu gdy pole już jest trafione, chybione lub już trafiono bombę
                                                continue; //pomijamy dalszą częśc kodu, pętla od nowa
                                            }
                                            if (aiBoard.isHit(row, col)) { //jeżeli poprzedni warunek nie był spełnione uruchamiamy funkcję sprawdzającą trafienie
                                                //gracz trafil statek komputera
                                                hitSound.play(); //odtworzenie dżwięku trafienia try warunek jest prawdziwy
                                                if (aiBoard.isGameOver()) { //sprawdzamy czy to koniec gry

                                                    gameOverSound.play(); //jeżeli warunek był prawdziwy to odtwarzamy dźwięk zakończenia gry

                                                    //ekran zakończenia gry
                                                    obiekt12.setTexture(&zakonczenie1);
                                                    playerBoard.draw(window, 0); //wyświetlenie na koniec stanu gry w tle, by można było zobaczyć jak wyglądała na koniec plansza
                                                    aiBoard.draw(window, 1); //wyświetlenie na koniec stanu gry w tle, by można było zobaczyć jak wyglądała na koniec plansza
                                                    window.draw(obiekt12);
                                                    window.display();

                                                    //czas do zniknięcia okna i powrót do menu (3s)
                                                    Clock clock;
                                                    while (clock.getElapsedTime().asSeconds() < 3.0f) {}
                                                    czyWyjsc = true;
                                                    break;
                                                }
                                            }
                                            else { //gracz nie trafil
                                                missSound.play(); // odpowiedni dźwięk
                                                sf::Event event;
                                                while (window.pollEvent(event)) {
                                                    //pusta pętla, która wyczyści kolejkę zdarzeń, aby nie zliczyć niepotrzebnych kliknięć myszki
                                                }
                                                playerTurn = false; //zmiana kolei
                                                obiekt1.setTexture(&komputermysli); //zmiana informacji o kolei
                                            }
                                        }
                                    }
                                    //"narysowanie" i wyświetlenie aktualnego stanu rozgrywki
                                    window.clear();
                                    window.draw(backgroundSprite1);
                                    playerBoard.draw(window, 0);
                                    aiBoard.draw(window, 1);
                                    window.draw(obiekt4);
                                    window.draw(obiekt11);
                                    window.draw(obiekt1);
                                    window.draw(button9);
                                    window.draw(button8a);
                                    window.display();
                                }
                                else { //kolej komputera
                                    int row = rand() % ROWS; //losuje rząd
                                    int col = rand() % COLS; //losuje kolumne
                                    while (playerBoard.m_cells[row][col] == CellState::Hit || playerBoard.m_cells[row][col] == CellState::Miss || playerBoard.m_cells[row][col] == CellState::hitBomb) { //jeżeli jest tam już coś co nie powinno być zaliczone to losuje do momentu, aż trafi na "wolne" pole
                                        row = rand() % ROWS;
                                        col = rand() % COLS;
                                    }
                                    Clock clock;
                                    while (clock.getElapsedTime().asSeconds() < 0.7f) {} //czas "myślenia" komputera
                                    if (playerBoard.isHit(row, col)) { //sprawdzenie czy komputer trafił
                                        //komputer trafil statek gracza
                                        hitSound.play();

                                        if (playerBoard.isGameOver()) { //sprawdzenie czy koniec gry

                                            gameOverSound.play();

                                            //ekran zakończenia gry
                                            obiekt12.setTexture(&zakonczenie2);
                                            playerBoard.draw(window, 0); //wyświetlenie na koniec stanu gry w tle, by można było zobaczyć jak wyglądała na koniec plansza
                                            aiBoard.draw(window, 1); //wyświetlenie na koniec stanu gry w tle, by można było zobaczyć jak wyglądała na koniec plansza
                                            window.draw(obiekt12);
                                            window.display();

                                            //czas do zniknięcia okna i powrót do menu (3s)
                                            Clock clock;
                                            while (clock.getElapsedTime().asSeconds() < 3.0f) {}
                                            czyWyjsc = true;
                                            break;
                                        }
                                    }
                                    else { //komputer chybił
                                        missSound.play();
                                        sf::Event event;
                                        while (window.pollEvent(event)) {
                                            //pusta pętla, która wyczyści kolejkę zdarzeń, aby nie zliczyć niepotrzebnych kliknięć myszki
                                        }
                                        playerTurn = true; //zmiana kolei
                                        obiekt1.setTexture(&twojakolej); //zmiana informacji o kolei

                                    }
                                    //"narysowanie" i wyświetlenie aktualnego stanu rozgrywki
                                    window.clear();
                                    window.draw(backgroundSprite1);
                                    playerBoard.draw(window, 0);
                                    aiBoard.draw(window, 1);
                                    window.draw(obiekt4);
                                    window.draw(obiekt11);
                                    window.draw(obiekt1);
                                    window.draw(button9);
                                    window.draw(button8a);
                                    window.display();

                                }
                            }
                            //"narysowanie" i wyświetlenie aktualnego stanu rozgrywki
                            window.clear();
                            window.draw(backgroundSprite1);
                            playerBoard.draw(window, 0);
                            aiBoard.draw(window, 1);
                            window.draw(obiekt4);
                            window.draw(obiekt11);
                            window.draw(obiekt1);
                            window.draw(button9);
                            window.draw(button8a);
                            window.display();

                        }
                    }
                    else { //gdy jest aktywny tryb Gracz vs Gracz

                        //rozpoczęcie gry
                        Board playerBoard(50, 50, SQUARE_SIZE);
                        Board aiBoard(600, 50, SQUARE_SIZE);
                        bool czyWyjsc2 = false;

                        //rozłożenie statków gracza nr1
                        int numShips = 10;
                        while (numShips > 0) {
                            Event event;
                            while (window.pollEvent(event)) {
                                if (event.type == Event::Closed) {
                                    window.close();
                                    return 0;
                                }
                                if (event.type == sf::Event::MouseMoved) { //gdy kursor się poruszył

                                    if (button9.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk odpowiadający za wyjście do menu
                                    {
                                        if (!isButton9Hovered) //jezeli nie był "podświetlony", to go "podświetla"
                                        {
                                            isButton9Hovered = true;
                                            button9.setTexture(&wyjscietlo1);
                                            placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                        }
                                    }
                                    else //jeżeli kursora nie ma na przycisku
                                    {
                                        if (isButton9Hovered) //jeżeli jest "podświetlony", to przywraca podstawową tekturę
                                        {
                                            isButton9Hovered = false;
                                            button9.setTexture(&wyjscietlo);
                                        }
                                    }
                                    if (button8a.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk włączający i wyłączający muzykę podczas rozgrywki
                                    {
                                        if (musicOn) {
                                            if (!isButton8aHovered) //jezeli nie był "podświetlony" i muzyka nie jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                            {
                                                isButton8aHovered = true;
                                                button8a.setTexture(&music4b);
                                                placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                            }
                                        }
                                        else {
                                            if (!isButton8aHovered) //jezeli nie był "podświetlony" i muzyka jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                            {
                                                isButton8aHovered = true;
                                                button8a.setTexture(&music5b);
                                                placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                            }
                                        }

                                    }
                                    else //jeżeli kursora nie ma na przycisku
                                    {
                                        if (musicOn) {
                                            if (isButton8aHovered) //jezeli był "podświetlony" i muzyka nie jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                            {
                                                isButton8aHovered = false;
                                                button8a.setTexture(&music4);
                                            }
                                        }
                                        else {
                                            if (isButton8aHovered) //jezeli był "podświetlony" i muzyka jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                            {
                                                isButton8aHovered = false;
                                                button8a.setTexture(&music5);
                                            }
                                        }
                                    }
                                    //inicjalizacja zmiennych potrzebnych do określenia czy kursor znajduje się nad planszą gracza
                                    int x = event.mouseMove.x - playerBoard.m_x;
                                    int y = event.mouseMove.y - playerBoard.m_y;
                                    int row = y / SQUARE_SIZE;
                                    int col = x / SQUARE_SIZE;

                                    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && playerBoard.m_cells[row][col] == CellState::Empty) { //sprawdzenie, czy kursor znajduje się na planszy gracza
                                        playerBoard.m_highlightedRow = row;  //ustawienie wiersza podświetlanego pola
                                        playerBoard.m_highlightedCol = col;  //ustawienie kolumny podświetlanego pola
                                    }
                                    else {
                                        playerBoard.m_highlightedRow = -1;  //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola
                                        playerBoard.m_highlightedCol = -1;  //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola
                                    }
                                }
                                else {
                                    playerBoard.m_highlightedRow = -1;  //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola (ta linia uniemożliwia zostawienie "niepotrzebnie podświetlonego pola" poza zakończeniu konretnych etapów rozgrywki)
                                    playerBoard.m_highlightedCol = -1;  //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola (ta linia uniemożliwia zostawienie "niepotrzebnie podświetlonego pola" poza zakończeniu konretnych etapów rozgrywki)
                                }

                                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) //jeżeli kliknięto lewy przycisk myszki
                                {
                                    if (button9.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk wyjścia do menu podczas rozgrywki
                                    {
                                        czyWyjsc2 = true; //wyjście do menu
                                    }
                                    else if (button8a.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk włączający i wyłączający muzykę podczas rozgrywki
                                    {
                                        if (musicOn) //wyciszamy muzykę i ustawiamy odpowiednią teksturę
                                        {
                                            button8a.setTexture(&music5);
                                            musicOn = false;
                                            backgroundMusic.setVolume(0);
                                        }
                                        else { //jeżeli była już wyciszona to ją odciszamy i przywracamy odpowiednią teksturę
                                            button8a.setTexture(&music4);
                                            musicOn = true;
                                            backgroundMusic.setVolume(1);
                                        }
                                    }
                                }

                                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) { //ustawianie statków, sprawdzanie czy i które pole na planszy kliknięto i wywołanie funkcji placeShip() dla playerBoard
                                    int x = event.mouseButton.x - playerBoard.m_x;
                                    int y = event.mouseButton.y - playerBoard.m_y;
                                    if (x > 0 && x < playerBoard.m_squareSize * COLS && y > 0 && y < playerBoard.m_squareSize * ROWS) {
                                        int row = y / SQUARE_SIZE;
                                        int col = x / SQUARE_SIZE;
                                        if (playerBoard.placeShip(row, col)) {
                                            numShips--;
                                            placeShipSound.play();
                                        }
                                    }
                                }
                            }
                            if (czyWyjsc2) //jeżeli prawda to wychodzimy z pętli
                            {
                                break;
                            }
                            //"rysowanie" i wyświetlanie obiektów
                            window.clear();
                            window.draw(backgroundSprite1);
                            playerBoard.draw(window, 0);
                            window.draw(obiekt5);
                            window.draw(obiekt6);
                            window.draw(obiekt9);
                            window.draw(button9);
                            window.draw(button8a);
                            window.display();

                        }
                        //"rysowanie" i wyświetlanie obiektów
                        window.clear();
                        window.draw(backgroundSprite1);
                        playerBoard.draw(window, 1);
                        window.draw(obiekt5);
                        window.draw(obiekt6);
                        window.draw(obiekt9);
                        window.draw(button9);
                        window.draw(button8a);
                        window.display();

                        if (czyWyjsc2)  //jeżeli prawda to wychodzimy do menu
                        {
                            break;
                        }

                        //rozłożenie statków gracza nr 2
                        cursorTexture.loadFromFile("grafika/kursorStatki48_2.png"); //ładujemy teksturę czerwonego odpowiednika kursora, by rozróżnić graczy i ustawiamy odpowiednie wartości
                        cursor.loadFromPixels(cursorTexture.copyToImage().getPixelsPtr(), cursorTexture.getSize(), { 0, 0 });
                        window.setMouseCursor(cursor);

                        numShips = 10;
                        while (numShips > 0) {
                            Event event;
                            while (window.pollEvent(event)) {
                                if (event.type == Event::Closed) {
                                    window.close();
                                    return 0;
                                }
                                if (event.type == sf::Event::MouseMoved) { //gdy kursor się poruszył

                                    if (button9.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk odpowiadający za wyjście do menu
                                    {
                                        if (!isButton9Hovered) //jezeli nie był "podświetlony", to go "podświetla"
                                        {
                                            isButton9Hovered = true;
                                            button9.setTexture(&wyjscietlo1);
                                            placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                        }
                                    }
                                    else //jeżeli kursora nie ma na przycisku
                                    {
                                        if (isButton9Hovered) //jeżeli jest "podświetlony", to przywraca podstawową tekturę
                                        {
                                            isButton9Hovered = false;
                                            button9.setTexture(&wyjscietlo);
                                        }
                                    }
                                    if (button8a.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk włączający i wyłączający muzykę podczas rozgrywki
                                    {
                                        if (musicOn) {
                                            if (!isButton8aHovered) //jezeli nie był "podświetlony" i muzyka nie jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                            {
                                                isButton8aHovered = true;
                                                button8a.setTexture(&music4b);
                                                placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                            }
                                        }
                                        else {
                                            if (!isButton8aHovered) //jezeli nie był "podświetlony" i muzyka jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                            {
                                                isButton8aHovered = true;
                                                button8a.setTexture(&music5b);
                                                placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                            }
                                        }

                                    }
                                    else //jeżeli kursora nie ma na przycisku
                                    {
                                        if (musicOn) {
                                            if (isButton8aHovered) //jezeli był "podświetlony" i muzyka nie jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                            {
                                                isButton8aHovered = false;
                                                button8a.setTexture(&music4);
                                            }
                                        }
                                        else {
                                            if (isButton8aHovered) //jezeli był "podświetlony" i muzyka jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                            {
                                                isButton8aHovered = false;
                                                button8a.setTexture(&music5);
                                            }
                                        }
                                    }
                                    //operacje wymagane do sprawdzenie czy kursor znajduje się nad planszą gracza nr 2 (użyczami aiBoard które działa tak potrzebujemy)
                                    int x = event.mouseMove.x - aiBoard.m_x;
                                    int y = event.mouseMove.y - aiBoard.m_y;
                                    int row = y / SQUARE_SIZE;
                                    int col = x / SQUARE_SIZE;

                                    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && aiBoard.m_cells[row][col] == CellState::Empty) {  //sprawdzamy czy kursor znajduje się nad planszą gracza nr2
                                        aiBoard.m_highlightedRow = row; //ustawienie wiersza podświetlanego pola
                                        aiBoard.m_highlightedCol = col; //ustawienie wiersza podświetlanego pola
                                    }
                                    else {
                                        aiBoard.m_highlightedRow = -1; //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola
                                        aiBoard.m_highlightedCol = -1; //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola
                                    }
                                }
                                else {
                                    aiBoard.m_highlightedRow = -1; //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola (ta linia uniemożliwia zostawienie "niepotrzebnie podświetlonego pola" poza zakończeniu konretnych etapów rozgrywki)
                                    aiBoard.m_highlightedCol = -1; //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola (ta linia uniemożliwia zostawienie "niepotrzebnie podświetlonego pola" poza zakończeniu konretnych etapów rozgrywki)
                                }

                                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) //jeżeli kliknięto lewy przycisk myszki
                                {
                                    if (button9.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk wyjścia do menu podczas rozgrywki
                                    {
                                        czyWyjsc2 = true; //wyjście do menu
                                    }
                                    else if (button8a.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk włączający i wyłączający muzykę podczas rozgrywki
                                    {
                                        if (musicOn) //wyciszamy muzykę i ustawiamy odpowiednią teksturę
                                        {
                                            button8a.setTexture(&music5);
                                            musicOn = false;
                                            backgroundMusic.setVolume(0);
                                        }
                                        else { //jeżeli była już wyciszona to ją odciszamy i przywracamy odpowiednią teksturę
                                            button8a.setTexture(&music4);
                                            musicOn = true;
                                            backgroundMusic.setVolume(1);
                                        }
                                    }
                                }

                                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) { //ustawianie statków, sprawdzanie czy i które pole na planszy kliknięto i wywołanie funkcji placeShip() dla aiBoard (plansza gracza nr 2)
                                    int x = event.mouseButton.x - aiBoard.m_x;
                                    int y = event.mouseButton.y - aiBoard.m_y;
                                    if (x > 0 && x < aiBoard.m_squareSize * COLS && y > 0 && y < aiBoard.m_squareSize * ROWS) {
                                        int row = y / SQUARE_SIZE;
                                        int col = x / SQUARE_SIZE;
                                        if (aiBoard.placeShip(row, col)) {
                                            numShips--;
                                            placeShipSound.play();
                                        }
                                    }
                                }
                            }

                            if (czyWyjsc2) //jeżeli prawda to wychodzimy z pętli
                            {
                                break;
                            }
                            //"rysowanie" i wyświetlanie obiektów
                            window.clear();
                            window.draw(backgroundSprite1);
                            aiBoard.draw(window, 0);
                            window.draw(obiekt5);
                            window.draw(obiekt6);
                            window.draw(obiekt10);
                            window.draw(button9);
                            window.draw(button8a);
                            window.display();
                        }
                        //"rysowanie" i wyświetlanie obiektów
                        window.clear();
                        window.draw(backgroundSprite1);
                        aiBoard.draw(window, 1);
                        window.draw(obiekt5);
                        window.draw(obiekt6);
                        window.draw(obiekt10);
                        window.draw(button9);
                        window.draw(button8a);
                        window.display();

                        if (czyWyjsc2) //jeżeli prawda to wracamy do menu
                        {
                            break;
                        }
                        obiekt1.setTexture(&kolejgraczanr1);

                        //rozłożenie bomb na planszy gracza (3 bomby)
                        if (czyBomba) {
                            int bomby = 3;
                            while (bomby > 0) {
                                int row = rand() % ROWS;
                                int col = rand() % COLS;
                                if (playerBoard.m_cells[row][col] == CellState::Empty) { //sprawdza czy pole jest "puste"

                                    if (playerBoard.placeBomb(row, col)) {
                                        bomby--;
                                    }
                                }
                            }
                        }

                        //rozłożenie bomb na planszy komputera (3 bomby)
                        if (czyBomba) {
                            int bomby = 3;
                            while (bomby > 0) {
                                int row = rand() % ROWS;
                                int col = rand() % COLS;
                                if (aiBoard.m_cells[row][col] == CellState::Empty) { //sprawdza czy pole jest "puste"

                                    if (aiBoard.placeBomb(row, col)) {
                                        bomby--;
                                    }
                                }
                            }
                        }

                        //część kodu i pętla fazy prób strzelania w statki 
                        bool playerTurn = true; //zaczyna gracz nr1
                        bool czyWyjsc = false; //inicjalizacja zmiennej odpowiadającej za powrót do menu
                        while (window.isOpen() && czyWyjsc == false) { //główna pętla rozgrywki Gracz vs Gracz
                            Event event;
                            while (window.pollEvent(event)) {
                                if (event.type == Event::Closed) {
                                    window.close();
                                    return 0;
                                }
                                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) //jeżeli kliknięto lewy przycisk myszki
                                {
                                    if (button9.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk wyjścia do menu podczas rozgrywki
                                    {
                                        czyWyjsc = true; //wyjście do menu
                                    }
                                    else if (button8a.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk włączający i wyłączający muzykę podczas rozgrywki
                                    {
                                        if (musicOn) //wyciszamy muzykę i ustawiamy odpowiednią teksturę
                                        {
                                            button8a.setTexture(&music5);
                                            musicOn = false;
                                            backgroundMusic.setVolume(0);
                                        }
                                        else { //jeżeli była już wyciszona to ją odciszamy i przywracamy odpowiednią teksturę
                                            button8a.setTexture(&music4);
                                            musicOn = true;
                                            backgroundMusic.setVolume(1);
                                        }
                                    }
                                }

                                if (playerTurn) { //jeżeli kolej gracza nr1
                                    cursorTexture.loadFromFile("grafika/kursorStatki48_1.png"); //ustawienie kursora na zielony odpowiednik
                                    cursor.loadFromPixels(cursorTexture.copyToImage().getPixelsPtr(), cursorTexture.getSize(), { 0, 0 });
                                    window.setMouseCursor(cursor);
                                    if (event.type == sf::Event::MouseMoved) { //gdy kursor się poruszył

                                    if (button9.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk odpowiadający za wyjście do menu
                                    {
                                        if (!isButton9Hovered) //jezeli nie był "podświetlony", to go "podświetla"
                                        {
                                            isButton9Hovered = true;
                                            button9.setTexture(&wyjscietlo1);
                                            placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                        }
                                    }
                                    else //jeżeli kursora nie ma na przycisku
                                    {
                                        if (isButton9Hovered) //jeżeli jest "podświetlony", to przywraca podstawową tekturę
                                        {
                                            isButton9Hovered = false;
                                            button9.setTexture(&wyjscietlo);
                                        }
                                    }
                                    if (button8a.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk włączający i wyłączający muzykę podczas rozgrywki
                                    {
                                        if (musicOn) {
                                            if (!isButton8aHovered) //jezeli nie był "podświetlony" i muzyka nie jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                            {
                                                isButton8aHovered = true;
                                                button8a.setTexture(&music4b);
                                                placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                            }
                                        }
                                        else {
                                            if (!isButton8aHovered) //jezeli nie był "podświetlony" i muzyka jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                            {
                                                isButton8aHovered = true;
                                                button8a.setTexture(&music5b);
                                                placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                            }
                                        }

                                    }
                                    else //jeżeli kursora nie ma na przycisku
                                    {
                                        if (musicOn) {
                                            if (isButton8aHovered) //jezeli był "podświetlony" i muzyka nie jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                            {
                                                isButton8aHovered = false;
                                                button8a.setTexture(&music4);
                                            }
                                        }
                                        else {
                                            if (isButton8aHovered) //jezeli był "podświetlony" i muzyka jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                            {
                                                isButton8aHovered = false;
                                                button8a.setTexture(&music5);
                                            }
                                        }
                                    }

                                    //inicjalizacja zmiennych potrzebnych do określenia czy kursor znajduje się nad planszą gracza nr2
                                    int x = event.mouseMove.x - aiBoard.m_x;
                                    int y = event.mouseMove.y - aiBoard.m_y;
                                    int row = y / SQUARE_SIZE;
                                    int col = x / SQUARE_SIZE;

                                    if (x > 0 && x < aiBoard.m_squareSize * COLS && y > 0 && y < aiBoard.m_squareSize * ROWS && (aiBoard.m_cells[row][col] == CellState::Empty || aiBoard.m_cells[row][col] == CellState::Ship || aiBoard.m_cells[row][col] == CellState::Bomb)) {  //sprawdzenie, czy kursor znajduje się na planszy gracza nr2 i na określonym statusie pola
                                        aiBoard.m_highlightedRow = row;  //ustawienie wiersza podświetlanego pola
                                        aiBoard.m_highlightedCol = col;  //ustawienie kolumny podświetlanego pola
                                    }
                                    else {
                                        aiBoard.m_highlightedRow = -1; //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola
                                        aiBoard.m_highlightedCol = -1; //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola
                                    }
                                }
                                else {
                                    aiBoard.m_highlightedRow = -1; //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola (ta linia uniemożliwia zostawienie "niepotrzebnie podświetlonego pola" poza zakończeniu konretnych etapów rozgrywki)
                                    aiBoard.m_highlightedCol = -1; //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola (ta linia uniemożliwia zostawienie "niepotrzebnie podświetlonego pola" poza zakończeniu konretnych etapów rozgrywki)
                                }
                                    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) { //gdy kliknięto lewy przycisk myszki
                                        int x = event.mouseButton.x - aiBoard.m_x; //przypisanie położenia
                                        int y = event.mouseButton.y - aiBoard.m_y; //przypisanie położenia
                                        if (x > 0 && x < aiBoard.m_squareSize * COLS && y > 0 && y < aiBoard.m_squareSize * ROWS) { //jeżeli zalicza tylko kliknięcia w obszarze planszy gracza nr2
                                            int row = y / SQUARE_SIZE;
                                            int col = x / SQUARE_SIZE;
                                            if (aiBoard.m_cells[row][col] == CellState::Hit || aiBoard.m_cells[row][col] == CellState::Miss || aiBoard.m_cells[row][col] == CellState::hitBomb) { //nie zalicza ruchu gdy pole już jest trafione, chybione lub już trafiono bombę
                                                continue; //pomijamy dalszą częśc kodu, pętla od nowa
                                            }
                                            if (aiBoard.isHit(row, col)) { //jeżeli poprzedni warunek nie był spełnione uruchamiamy funkcję sprawdzającą trafienie
                                                //gracz nr1 trafil statek gracza nr2
                                                hitSound.play(); //odtworzenie dżwięku trafienia try warunek jest prawdziwy
                                                if (aiBoard.isGameOver()) { //sprawdzamy czy to koniec gry

                                                    gameOverSound.play(); //jeżeli warunek był prawdziwy to odtwarzamy dźwięk zakończenia gry

                                                    //ekran zakończenia gry
                                                    obiekt12.setTexture(&zakonczenie3);
                                                    playerBoard.draw(window, 1); //wyświetlenie na koniec stanu gry w tle, by można było zobaczyć jak wyglądała na koniec plansza
                                                    aiBoard.draw(window, 1); //wyświetlenie na koniec stanu gry w tle, by można było zobaczyć jak wyglądała na koniec plansza
                                                    window.draw(obiekt12);
                                                    window.display();

                                                    //czas do zniknięcia okna i powrót do menu (3s)
                                                    Clock clock;
                                                    while (clock.getElapsedTime().asSeconds() < 3.0f) {}
                                                    czyWyjsc = true;
                                                    break;
                                                }
                                            }
                                            else { //gracz nr1 nie trafił
                                                missSound.play();
                                                playerTurn = false; //zmiana kolejki
                                                obiekt1.setTexture(&kolejgraczanr2);
                                            }
                                        }
                                    }
                                    //"rysowanie" i wyświetlanie obiektów
                                    window.clear();
                                    window.draw(backgroundSprite1);
                                    playerBoard.draw(window, 1);
                                    aiBoard.draw(window, 1);
                                    window.draw(obiekt5);
                                    window.draw(obiekt6);
                                    window.draw(obiekt1);
                                    window.draw(button9);
                                    window.draw(button8a);
                                    window.display();
                                }
                                else { //kolej gracza nr2
                                    cursorTexture.loadFromFile("grafika/kursorStatki48_2.png"); //zmiana tekstury kursora na czerowny odpowiednik
                                    cursor.loadFromPixels(cursorTexture.copyToImage().getPixelsPtr(), cursorTexture.getSize(), { 0, 0 });
                                    window.setMouseCursor(cursor);

                                    if (event.type == sf::Event::MouseMoved) { //gdy kursor się poruszył
                                        if (button9.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk odpowiadający za wyjście do menu
                                        {
                                            if (!isButton9Hovered) //jezeli nie był "podświetlony", to go "podświetla"
                                            {
                                                isButton9Hovered = true;
                                                button9.setTexture(&wyjscietlo1);
                                                placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                            }
                                        }
                                        else //jeżeli kursora nie ma na przycisku
                                        {
                                            if (isButton9Hovered) //jeżeli jest "podświetlony", to przywraca podstawową tekturę
                                            {
                                                isButton9Hovered = false;
                                                button9.setTexture(&wyjscietlo);
                                            }
                                        }
                                        if (button8a.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk włączający i wyłączający muzykę podczas rozgrywki
                                        {
                                            if (musicOn) {
                                                if (!isButton8aHovered) //jezeli nie był "podświetlony" i muzyka nie jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                                {
                                                    isButton8aHovered = true;
                                                    button8a.setTexture(&music4b);
                                                    placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                                }
                                            }
                                            else {
                                                if (!isButton8aHovered) //jezeli nie był "podświetlony" i muzyka jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                                {
                                                    isButton8aHovered = true;
                                                    button8a.setTexture(&music5b);
                                                    placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                                }
                                            }

                                        }
                                        else //jeżeli kursora nie ma na przycisku
                                        {
                                            if (musicOn) {
                                                if (isButton8aHovered) //jezeli był "podświetlony" i muzyka nie jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                                {
                                                    isButton8aHovered = false;
                                                    button8a.setTexture(&music4);
                                                }
                                            }
                                            else {
                                                if (isButton8aHovered) //jezeli był "podświetlony" i muzyka jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                                {
                                                    isButton8aHovered = false;
                                                    button8a.setTexture(&music5);
                                                }
                                            }
                                        }
                                        //sprawdzenie czy kursor najechał na planszę gracza nr1
                                        int x = event.mouseMove.x - playerBoard.m_x;
                                        int y = event.mouseMove.y - playerBoard.m_y;
                                        int row = y / SQUARE_SIZE;
                                        int col = x / SQUARE_SIZE;

                                        if (x > 0 && x < playerBoard.m_squareSize * COLS && y > 0 && y < playerBoard.m_squareSize * ROWS && (playerBoard.m_cells[row][col] == CellState::Empty || playerBoard.m_cells[row][col] == CellState::Ship || playerBoard.m_cells[row][col] == CellState::Bomb)) {  //jeżeli kursor znajduje się na planszy gracza nr1 i spełnia podane warunki to zostanie te pole "podświetlone"
                                            playerBoard.m_highlightedRow = row; //ustawienie wiersza podświetlanego pola
                                            playerBoard.m_highlightedCol = col; //ustawienie wiersza podświetlanego pola
                                        }
                                        else {
                                            playerBoard.m_highlightedRow = -1; //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola
                                            playerBoard.m_highlightedCol = -1; //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola
                                        }
                                    }
                                    else {
                                        playerBoard.m_highlightedRow = -1; //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola (ta linia uniemożliwia zostawienie "niepotrzebnie podświetlonego pola" poza zakończeniu konretnych etapów rozgrywki)
                                        playerBoard.m_highlightedCol = -1; //jeśli kursor jest poza planszą, zostanie zresetowana wartość podświetlonego pola (ta linia uniemożliwia zostawienie "niepotrzebnie podświetlonego pola" poza zakończeniu konretnych etapów rozgrywki)
                                    }
                                    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) { //jeżeli kliknięto lewy przycisk myszki
                                        int x = event.mouseButton.x - playerBoard.m_x;
                                        int y = event.mouseButton.y - playerBoard.m_y;
                                        if (x > 0 && x < playerBoard.m_squareSize * COLS && y > 0 && y < playerBoard.m_squareSize * ROWS) { //zarerestrowanie tylko kliknięcia na planszy gracza nr1
                                            int row = y / SQUARE_SIZE;
                                            int col = x / SQUARE_SIZE;
                                            if (playerBoard.m_cells[row][col] == CellState::Hit || playerBoard.m_cells[row][col] == CellState::Miss || playerBoard.m_cells[row][col] == CellState::hitBomb) { //uniemożliwienie trafienia pola, które nie jest do tego przeznaczone
                                                continue;
                                            }
                                            if (playerBoard.isHit(row, col)) { //jeżeli trafiono statek
                                                //gracz nr2 trafil statek gracza nr 1
                                                hitSound.play();

                                                if (playerBoard.isGameOver()) { //sprawdzenie czy koniec gry

                                                    gameOverSound.play();

                                                    //ekran końcowy
                                                    obiekt12.setTexture(&zakonczenie4);
                                                    playerBoard.draw(window, 1); //wyświetlenie na koniec stanu gry w tle, by można było zobaczyć jak wyglądała na koniec plansza 
                                                    aiBoard.draw(window, 1); //wyświetlenie na koniec stanu gry w tle, by można było zobaczyć jak wyglądała na koniec plansza
                                                    window.draw(obiekt12);
                                                    window.display();

                                                    //czas do zniknięcia okna i powrót do menu (3s)
                                                    Clock clock;
                                                    while (clock.getElapsedTime().asSeconds() < 3.0f) {}
                                                    czyWyjsc = true;
                                                    break;
                                                }
                                            }
                                            else { //gracz nr2 nie trafił
                                                missSound.play();
                                                playerTurn = true; //zmiana kolei
                                                obiekt1.setTexture(&kolejgraczanr1);
                                            }
                                        }
                                    }
                                    //"rysowanie" i wyświetlanie obiektów
                                    window.clear();
                                    window.draw(backgroundSprite1);
                                    playerBoard.draw(window, 1);
                                    aiBoard.draw(window, 1);
                                    window.draw(obiekt5);
                                    window.draw(obiekt6);
                                    window.draw(obiekt1);
                                    window.draw(button9);
                                    window.draw(button8a);
                                    window.display();
                                }
                            }
                            //"rysowanie" i wyświetlanie obiektów
                            window.clear();
                            window.draw(backgroundSprite1);
                            playerBoard.draw(window, 1);
                            aiBoard.draw(window, 1);
                            window.draw(obiekt5);
                            window.draw(obiekt6);
                            window.draw(obiekt1);
                            window.draw(button9);
                            window.draw(button8a);
                            window.display();

                        }
                    }
                }
                else if (button2.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //gdy kliknięto przycisk tryb
                {
                    bool window1 = true; //potrzebne do powrotu do menu
                    button4.setTexture(&graczvsgracz);
                    button5.setTexture(&graczvsai);
                    button6.setTexture(&bomby2); //tekstura zablokowanego przycisku
                    button7.setTexture(&bezbomb2); //tekstura zablokowanego przycisku
                    while (window.isOpen() && window1) {
                        sf::Event event;
                        while (window.pollEvent(event))
                        {
                            if (event.type == sf::Event::Closed)
                                window.close();

                            if (event.type == sf::Event::MouseMoved) //gdy kursor się poruszy
                            {
                                if (button4.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //jeżeli znajdzie się nad przyciskiem gracz vs gracz
                                {
                                    if (!isButton4Hovered) //jeżeli przycisk nie jest "podświetlony" to zostaje "podświetlony"
                                    {
                                        isButton4Hovered = true;
                                        button4.setTexture(&graczvsgracz1);
                                        placeShipSound.play();
                                    }
                                }
                                else //jeżeli kursor już nie będzie na przycisku
                                {
                                    if (isButton4Hovered) //jeżeli przycisk jest "podświetlony", to już nie jest 
                                    {
                                        isButton4Hovered = false;
                                        button4.setTexture(&graczvsgracz);
                                    }
                                }

                                if (button5.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //jeżeli znajdzie się nad przyciskiem gracz vs ai
                                {
                                    if (!isButton5Hovered) //jeżeli przycisk nie jest "podświetlony" to zostaje "podświetlony"
                                    {
                                        isButton5Hovered = true;
                                        button5.setTexture(&graczvsai1);
                                        placeShipSound.play();
                                    }
                                }
                                else //jeżeli kursor już nie będzie na przycisku
                                {
                                    if (isButton5Hovered) //jeżeli przycisk jest "podświetlony", to już nie jest
                                    {
                                        isButton5Hovered = false;
                                        button5.setTexture(&graczvsai);
                                    }
                                }

                                if (button8.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk włączający i wyłączający muzykę w menu
                                {
                                    if (musicOn) {
                                        if (!isButton8Hovered) //jezeli nie był "podświetlony" i muzyka nie jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                        {
                                            isButton8Hovered = true;
                                            button8.setTexture(&music1);
                                            placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                        }
                                    }
                                    else {
                                        if (!isButton8Hovered) //jezeli nie był "podświetlony" i muzyka jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                        {
                                            isButton8Hovered = true;
                                            button8.setTexture(&music2b);
                                            placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                        }
                                    }

                                }
                                else //jeżeli kursora nie ma na przycisku
                                {
                                    if (musicOn) {
                                        if (isButton8Hovered) //jezeli był "podświetlony" i muzyka nie jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                        {
                                            isButton8Hovered = false;
                                            button8.setTexture(&music);
                                        }
                                    }
                                    else {
                                        if (isButton8Hovered) //jezeli był "podświetlony" i muzyka jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                        {
                                            isButton8Hovered = false;
                                            button8.setTexture(&music2);
                                        }
                                    }
                                }
                            }

                            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) //jeżeli kliknięto lewy przycisk myszki
                            {
                                if (button4.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknieto przycisk gracz vs gracz
                                {
                                    graczVSgracz = true; //włączono tryb gracz vs gracz
                                    bool window2 = true; //potrzebne do wyjścia z pętli i wrócenia do menu
                                    button4.setTexture(&graczvsgracz2); //tekstura zablokowanego przycisku
                                    button5.setTexture(&graczvsai2); //tekstura zablokowanego przycisku
                                    button6.setTexture(&bomby);
                                    button7.setTexture(&bezbomb);
                                    while (window.isOpen() && window2) {
                                        Event event;
                                        while (window.pollEvent(event)) {
                                            if (event.type == Event::Closed) {
                                                window.close();
                                                return 0;
                                            }
                                            if (event.type == sf::Event::MouseMoved) //gdy kursor się poruszy
                                            {
                                                if (button6.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //jeżeli znajdzie się nad przyciskiem bomby
                                                {
                                                    if (!isButton6Hovered) //jeżeli przycisk nie jest "podświetlony" to zostaje "podświetlony"
                                                    {
                                                        isButton6Hovered = true;
                                                        button6.setTexture(&bomby1);
                                                        placeShipSound.play();
                                                    }
                                                }
                                                else //jeżeli kursor nie jest już na przycisku
                                                {
                                                    if (isButton6Hovered) //jeżeli przycisk jest "podświetlony", to już nie jest
                                                    {
                                                        isButton6Hovered = false;
                                                        button6.setTexture(&bomby);
                                                    }
                                                }
                                                if (button7.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //jeżeli znajdzie się nad przyciskiem bez bomby
                                                {
                                                    if (!isButton7Hovered) //jeżeli przycisk nie jest "podświetlony" to zostaje "podświetlony"
                                                    {
                                                        isButton7Hovered = true;
                                                        button7.setTexture(&bezbomb1);
                                                        placeShipSound.play();
                                                    }
                                                }
                                                else //jeżeli kursor nie jest już na przycisku
                                                {
                                                    if (isButton7Hovered) //jeżeli przycisk jest "podświetlony", to już nie jest
                                                    {
                                                        isButton7Hovered = false;
                                                        button7.setTexture(&bezbomb);
                                                    }
                                                }

                                                if (button8.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk włączający i wyłączający muzykę w menu
                                                {
                                                    if (musicOn) {
                                                        if (!isButton8Hovered) //jezeli nie był "podświetlony" i muzyka nie jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                                        {
                                                            isButton8Hovered = true;
                                                            button8.setTexture(&music1);
                                                            placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                                        }
                                                    }
                                                    else {
                                                        if (!isButton8Hovered) //jezeli nie był "podświetlony" i muzyka jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                                        {
                                                            isButton8Hovered = true;
                                                            button8.setTexture(&music2b);
                                                            placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                                        }
                                                    }

                                                }
                                                else //jeżeli kursora nie ma na przycisku
                                                {
                                                    if (musicOn) {
                                                        if (isButton8Hovered) //jezeli był "podświetlony" i muzyka nie jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                                        {
                                                            isButton8Hovered = false;
                                                            button8.setTexture(&music);
                                                        }
                                                    }
                                                    else {
                                                        if (isButton8Hovered) //jezeli był "podświetlony" i muzyka jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                                        {
                                                            isButton8Hovered = false;
                                                            button8.setTexture(&music2);
                                                        }
                                                    }
                                                }
                                            }

                                            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) //jeżeli kliknięto lewy przycisk myszki
                                            {
                                                if (button6.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk bomby
                                                {
                                                    czyBomba = true; //włączono tryb z bombami
                                                    window1 = false; //wychodzimy z pętli do menu
                                                    window2 = false; //wychodzimy z pętli do menu
                                                }
                                                else if (button7.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk bez bomb
                                                {
                                                    czyBomba = false; //wyłączono tryb z bombami
                                                    window1 = false; //wychodzimy z pętli do menu
                                                    window2 = false; //wychodzimy z pętli do menu
                                                } 
                                                else if (button8.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk włączjący i wyłączjacy muzykę w tle
                                                {
                                                    if (musicOn) //gdy muzyka nie jest wyciszona - wyciszamy
                                                    {
                                                        button8.setTexture(&music2);
                                                        musicOn = false;
                                                        backgroundMusic.setVolume(0);
                                                    }
                                                    else { //gdy jest wyciszona - włączamy ją
                                                        button8.setTexture(&music);
                                                        musicOn = true;
                                                        backgroundMusic.setVolume(1);
                                                    }
                                                }
                                            }
                                            //"rysowanie" i wyświetlanie obiektów
                                            window.clear();
                                            window.draw(backgroundSprite);
                                            window.draw(button4);
                                            window.draw(button5);
                                            window.draw(button6);
                                            window.draw(button7);
                                            window.draw(button8);
                                            window.draw(obiekt13);
                                            window.display();
                                        }

                                    }

                                }
                                else if (button5.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknieto przycisk gracz vs ai
                                {
                                    graczVSgracz = false; //wyłączamy tryb gracz vs gracz, jest teraz gracz vs ai
                                    bool window2 = true;
                                    button4.setTexture(&graczvsgracz2); //tekstura zablokowanego przycisku
                                    button5.setTexture(&graczvsai2); //tekstura zablokowanego przycisku
                                    button6.setTexture(&bomby);
                                    button7.setTexture(&bezbomb);
                                    while (window.isOpen() && window2) {
                                        Event event;
                                        while (window.pollEvent(event)) {
                                            if (event.type == Event::Closed) {
                                                window.close();
                                                return 0;
                                            }
                                            if (event.type == sf::Event::MouseMoved) //gdy poruszono kursorem
                                            {
                                                if (button6.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //jeżeli znajdzie się nad przyciskiem bomby
                                                {
                                                    if (!isButton6Hovered) //jeżeli przycisk nie jest "podświetlony" to zostaje "podświetlony"
                                                    {
                                                        isButton6Hovered = true;
                                                        button6.setTexture(&bomby1);
                                                        placeShipSound.play();
                                                    }
                                                }
                                                else //jeżeli kursor nie jest już na przycisku
                                                {
                                                    if (isButton6Hovered) //jeżeli przycisk jest "podświetlony", to już nie jest
                                                    {
                                                        isButton6Hovered = false;
                                                        button6.setTexture(&bomby);
                                                    }
                                                }
                                                if (button7.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //jeżeli znajdzie się nad przyciskiem bez bomby
                                                {
                                                    if (!isButton7Hovered) //jeżeli przycisk nie jest "podświetlony" to zostaje "podświetlony"
                                                    {
                                                        isButton7Hovered = true;
                                                        button7.setTexture(&bezbomb1);
                                                        placeShipSound.play();
                                                    }
                                                }
                                                else //jeżeli kursor nie jest już na przycisku
                                                {
                                                    if (isButton7Hovered) //jeżeli przycisk jest "podświetlony", to już nie jest
                                                    {
                                                        isButton7Hovered = false;
                                                        button7.setTexture(&bezbomb);
                                                    }
                                                }

                                                if (button8.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))) //sprawdza, czy kursor najechał na przycisk włączający i wyłączający muzykę w menu
                                                {
                                                    if (musicOn) {
                                                        if (!isButton8Hovered) //jezeli nie był "podświetlony" i muzyka nie jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                                        {
                                                            isButton8Hovered = true;
                                                            button8.setTexture(&music1);
                                                            placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                                        }
                                                    }
                                                    else {
                                                        if (!isButton8Hovered) //jezeli nie był "podświetlony" i muzyka jest wyciszona, to go "podświetla" tekturą odpowiednią do stanu muzyki
                                                        {
                                                            isButton8Hovered = true;
                                                            button8.setTexture(&music2b);
                                                            placeShipSound.play(); //odtwarzany jest dźwięk kładzenia statku (pasuje idealnie)
                                                        }
                                                    }

                                                }
                                                else //jeżeli kursora nie ma na przycisku
                                                {
                                                    if (musicOn) {
                                                        if (isButton8Hovered) //jezeli był "podświetlony" i muzyka nie jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                                        {
                                                            isButton8Hovered = false;
                                                            button8.setTexture(&music);
                                                        }
                                                    }
                                                    else {
                                                        if (isButton8Hovered) //jezeli był "podświetlony" i muzyka jest wyciszona, to przywraca odpowiednio podstawową tekturę
                                                        {
                                                            isButton8Hovered = false;
                                                            button8.setTexture(&music2);
                                                        }
                                                    }
                                                }
                                            }

                                            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) //jeżeli kliknięto lewy przycisk myszki
                                            {
                                                if (button6.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk bomby
                                                {
                                                    czyBomba = true; //włączono tryb z bombami
                                                    window1 = false; //wychodzimy z pętli do menu
                                                    window2 = false; //wychodzimy z pętli do menu
                                                }
                                                else if (button7.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk bez bomb
                                                {
                                                    czyBomba = false; //wyłączono tryb z bombami
                                                    window1 = false; //wychodzimy z pętli do menu
                                                    window2 = false; //wychodzimy z pętli do menu
                                                }
                                                else if (button8.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk włączjący i wyłączjacy muzykę w tle
                                                {
                                                    if (musicOn) //gdy muzyka nie jest wyciszona - wyciszamy
                                                    {
                                                        button8.setTexture(&music2);
                                                        musicOn = false;
                                                        backgroundMusic.setVolume(0);
                                                    }
                                                    else { //gdy jest wyciszona - włączamy ją
                                                        button8.setTexture(&music);
                                                        musicOn = true;
                                                        backgroundMusic.setVolume(1);
                                                    }
                                                }
                                            }
                                            //"rysowanie" i wyświetlanie obiektów
                                            window.clear();
                                            window.draw(backgroundSprite);
                                            window.draw(button4);
                                            window.draw(button5);
                                            window.draw(button6);
                                            window.draw(button7);
                                            window.draw(button8);
                                            window.draw(obiekt13);
                                            window.display();
                                        }

                                    }

                                }
                                else if (button8.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk włączjący i wyłączjacy muzykę w tle
                                {
                                    if (musicOn) //gdy muzyka nie jest wyciszona - wyciszamy
                                    {
                                        button8.setTexture(&music2);
                                        musicOn = false;
                                        backgroundMusic.setVolume(0);
                                    }
                                    else { //gdy jest wyciszona - włączamy ją
                                        button8.setTexture(&music);
                                        musicOn = true;
                                        backgroundMusic.setVolume(1);
                                    }
                                }
                            }
                            //"rysowanie" i wyświetlanie obiektów
                            window.clear();
                            window.draw(backgroundSprite);
                            window.draw(button4);
                            window.draw(button5);
                            window.draw(button6);
                            window.draw(button7);
                            window.draw(button8);
                            window.draw(obiekt13);
                            window.display();
                        }

                    }
                }
                else if (button3.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //gdy kliknięto przycisk wyjscie
                {
                    //wychodzimy z gry
                    window.close();
                }
                else if (button8.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))) //jeżeli kliknięto przycisk włączjący i wyłączjacy muzykę w tle
                {
                    if (musicOn) //gdy muzyka nie jest wyciszona - wyciszamy
                    {
                        button8.setTexture(&music2);
                        musicOn = false;
                        backgroundMusic.setVolume(0);
                    }
                    else { //gdy jest wyciszona - włączamy ją
                        button8.setTexture(&music);
                        musicOn = true;
                        backgroundMusic.setVolume(1);
                    }
                                }
            }
        }
        //"rysowanie" i wyświetlanie obiektów
        window.clear();
        window.draw(backgroundSprite);
        window.draw(button1);
        window.draw(button2);
        window.draw(button3);
        window.draw(button8);
        window.draw(obiekt13);
        window.display();
    }
    return 0;
}