#include "Silnik.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include <filesystem>

/**
 * @brief Konstruktor klasy Silnik.
 * Inicjalizuje okno g³ówne oraz ustawia domyœlne wartoœci dla zmiennych.
 */
Silnik::Silnik() : window(sf::VideoMode(800, 600), "Silnik 2D", sf::Style::Close), aktualnyObiekt(nullptr), czyWypelnione(false), kolor(sf::Color::White),
trybEdycji(false), kolorEdycji(sf::Color::Red), obiektDoEdycji(nullptr), kolorWyboru(sf::Color::White) {}

/**
 * @brief Destruktor klasy Silnik.
 * Zajmuje siê zwalnianiem pamiêci zarezerwowanej dla obiektów graficznych.
 */
Silnik::~Silnik() {
    for (auto& obiekt : obiekty) {
        delete obiekt;
    }
}
/**
 * @brief Metoda wczytuj¹ca teksturê z pliku i ustawiaj¹ca j¹ jako wype³nienie obiektu.
 * W zale¿noœci od typu obiektu (Kolo, Trojkat, Prostokat) wczytuje teksturê
 * i przypisuje j¹ jako wype³nienie obiektu.
 * @param obiekt WskaŸnik do obiektu graficznego, dla którego ma byæ wczytana tekstura.
 * @param sciezkaObrazu Œcie¿ka do pliku z obrazem.
 */
void Silnik::wczytajObraz(sf::Drawable* obiekt, const std::string& sciezkaObrazu) {
    if (Kolo* kolo = dynamic_cast<Kolo*>(obiekt)) {
        // Wczytuje obraz jako teksturê
        sf::Texture texture;
        if (texture.loadFromFile(sciezkaObrazu)) {
            //Ustawia teksturê jako wype³nienie kszta³tu
            kolo->ustawWypelnienie(texture);

            //Usuwa wype³nienie kolorem
            czyWypelnione = false;

            std::cout << "Tekstura wczytana poprawnie dla ko³a.\n";
        }
       
    }
    else if (Trojkat* trojkat = dynamic_cast<Trojkat*>(obiekt)) {
        //Wczytuje obraz jako teksturê
        sf::Texture texture;
        if (texture.loadFromFile(sciezkaObrazu)) {
            // Ustawia teksturê jako wype³nienie kszta³tu
            trojkat->ustawWypelnienie(texture);

            //Usuwa wype³nienie kolorem
            czyWypelnione = false;

            std::cout << "Tekstura wczytana poprawnie dla trójk¹ta.\n";
        }
    }
    else if (Prostokat* prostokat = dynamic_cast<Prostokat*>(obiekt)) {
        //Wczytuje obraz jako teksturê
        sf::Texture texture;
        if (texture.loadFromFile(sciezkaObrazu)) {
            //Ustawia teksturê jako wype³nienie kszta³tu
            prostokat->ustawWypelnienie(texture);

            //Usuwa wype³nienie kolorem
            czyWypelnione = false;

            std::cout << "Tekstura wczytana poprawnie dla prostok¹ta.\n";
        }
    }
}
/**
 * @brief Metoda otwieraj¹ca okno dialogowe do wyboru pliku.
 * Pozwala u¿ytkownikowi wprowadziæ œcie¿kê do pliku.
 * @return Wprowadzona przez u¿ytkownika œcie¿ka do pliku.
 */
std::string otworzOknoDialogowe() {
    std::string sciezka;

    sf::RenderWindow fileDialog(sf::VideoMode(800, 200), "Wybierz plik", sf::Style::Titlebar | sf::Style::Close);
    fileDialog.setPosition(sf::Vector2i(fileDialog.getPosition().x + 50, fileDialog.getPosition().y + 50));

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Nie mo¿na za³adowaæ czcionki.\n";
    }

    sf::Text directoryText;
    directoryText.setFont(font);
    directoryText.setCharacterSize(16);
    directoryText.setPosition(10, 10);
    directoryText.setFillColor(sf::Color::White);

    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(16);
    inputText.setPosition(10, 70);
    inputText.setFillColor(sf::Color::White);
    inputText.setString("Wprowadz sciezke:");

    sf::String userInput;

    while (fileDialog.isOpen()) {
        sf::Event event;
        while (fileDialog.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                fileDialog.close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                fileDialog.close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                //Ustawia wybran¹ œcie¿kê
                sciezka = userInput;
                fileDialog.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == 8 && !userInput.isEmpty()) {
                        //Obs³uguje backspace
                        userInput.erase(userInput.getSize() - 1, 1);
                    }
                    else if (event.text.unicode != 8) {
                        //Dodaje znak do userInput (ignorujuje backspace)
                        userInput += static_cast<char>(event.text.unicode);
                    }
                }
            }
        }

        directoryText.setString("Aktualny katalog: " + std::filesystem::current_path().string());
        inputText.setString("Wprowadz sciezke: " + userInput);

        fileDialog.clear(sf::Color::Black);
        fileDialog.draw(directoryText);
        fileDialog.draw(inputText);
        fileDialog.display();
    }

    return userInput;
}
/**
 * @brief Metoda uruchamiaj¹ca g³ówn¹ pêtlê programu.
 * Obs³uguje zdarzenia okna, rysuje obiekty i reaguje na akcje u¿ytkownika.
 */
void Silnik::uruchom() {
    renderTexture.create(window.getSize().x, window.getSize().y);
    sf::Sprite sprite(renderTexture.getTexture());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            obslugaZdarzen(event);
        }

        renderTexture.clear(sf::Color::Black);
        rysujObiekty();

        if (trybEdycji && obiektDoEdycji) {
            renderTexture.draw(*obiektDoEdycji);
        }
        else if (aktualnyObiekt) {
            renderTexture.draw(*aktualnyObiekt);
        }

        renderTexture.display();

        window.clear();
        window.draw(sprite);

        for (auto& obiekt : obiekty) {
            window.draw(*obiekt);
        }

        window.display();
    }
}
/**
 * @brief Metoda rysuj¹ca wszystkie obiekty w oknie.
 * Wykorzystuje dynamiczne rzutowanie dla obiektów sf::Transformable
 * w celu uwzglêdnienia ewentualnych transformacji.
 */
void Silnik::rysujObiekty() {
    for (auto& obiekt : obiekty) {
        //Sprawdza, czy obiekt jest zainicjalizowany
        if (obiekt) {
            //Dynamiczne rzutowanie na sf::Transformable
            sf::Transformable* transformableObj = dynamic_cast<sf::Transformable*>(obiekt);

            if (transformableObj) {
                window.draw(*obiekt, transformableObj->getTransform());
            }
            else {
                //Jeœli obiekt nie dziedziczy po sf::Transformable, rysuje bez transformacji
                window.draw(*obiekt);
            }
        }
    }
}
/**
 * @brief Metoda obs³uguj¹ca zdarzenia okna, takie jak ruch myszy czy klawisze.
 * Reaguje na ró¿ne zdarzenia, m.in. tworzy, edytuje, przesuwa i obraca obiekty.
 * @param event Zdarzenie sf::Event, które ma zostaæ obs³u¿one.
 */
void Silnik::obslugaZdarzen(const sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    else if (event.type == sf::Event::MouseMoved) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && aktualnyObiekt) {
            punktKoncowy = Point2D(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));

            if (Linia* linia = dynamic_cast<Linia*>(aktualnyObiekt)) {
                linia->ustawPunkty(punktStartowy, punktKoncowy);
            }
            else if (Kolo* kolo = dynamic_cast<Kolo*>(aktualnyObiekt)) {
                float promien = std::sqrt(std::pow(punktKoncowy.x - punktStartowy.x, 2) + std::pow(punktKoncowy.y - punktStartowy.y, 2));
                kolo->ustawPunkty(punktStartowy, promien);
            }
            else if (Trojkat* trojkat = dynamic_cast<Trojkat*>(aktualnyObiekt)) {
                trojkat->ustawPunkty(punktStartowy, Point2D(event.mouseMove.x, event.mouseMove.y), Point2D(event.mouseButton.x, event.mouseButton.x));
            }
            else if (Prostokat* prostokat = dynamic_cast<Prostokat*>(aktualnyObiekt)) {
                prostokat->ustawPunkty(punktStartowy, punktKoncowy);
            }
        }

        //Wyœwietlenie obecnego obiektu w trakcie rysowania
        window.clear(sf::Color::Black);
        rysujObiekty();
        if (trybEdycji && obiektDoEdycji) {
            window.draw(*obiektDoEdycji);
        }
        else if (aktualnyObiekt) {
            window.draw(*aktualnyObiekt);
        }
        window.display();
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::O) {
            //Otwórz okno dialogowe do wyboru pliku
            std::string sciezka = otworzOknoDialogowe();
            if (!sciezka.empty()) {
                sciezkaObrazu = sciezka;

            }
        }
        if (event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
        else if (event.key.code == sf::Keyboard::Q) {
            delete aktualnyObiekt;
            kolor = kolorWyboru;
            aktualnyObiekt = new Linia(punktStartowy, punktKoncowy, kolor);
        }
        else if (event.key.code == sf::Keyboard::W) {
            delete aktualnyObiekt;
            kolor = kolorWyboru;
            //Inicjalizacja promienia
            promien = std::sqrt(std::pow(punktKoncowy.x - punktStartowy.x, 2) + std::pow(punktKoncowy.y - punktStartowy.y, 2));

            aktualnyObiekt = new Kolo(punktStartowy, promien, kolorWyboru, czyWypelnione);
        }
        else if (event.key.code == sf::Keyboard::E) {
            delete aktualnyObiekt;
            kolor = kolorWyboru;
            aktualnyObiekt = new Trojkat(punktA, punktB, punktC, kolor, czyWypelnione);
        }
        else if (event.key.code == sf::Keyboard::R) {
            delete aktualnyObiekt;
            kolor = kolorWyboru;
            //Inicjalizacja punktów prostok¹ta
            punktA = punktStartowy;
            punktB = punktKoncowy;

            aktualnyObiekt = new Prostokat(punktA, punktB, kolorWyboru, czyWypelnione);
        }
        else if (event.key.code == sf::Keyboard::Y) {
            czyWypelnione = !czyWypelnione;
        }
        
        else if (event.key.code == sf::Keyboard::U) {
            trybEdycji = !trybEdycji;
            if (trybEdycji) {
                std::cout << "Tryb edycji wlaczony.\n";
                if (!obiektDoEdycji) {
                    std::cout << "Wybierz obiekt do edycji.\n";
                }
            }
            else {
                std::cout << "Tryb edycji wylaczony.\n";
                obiektDoEdycji = nullptr;
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            punktStartowy = Point2D(event.mouseButton.x, event.mouseButton.y);
            punktKoncowy = punktStartowy;

            //Stworzenie kopii obecnego obiektu do edycji w trakcie rysowania (przez to rysowana jest linia czasami mimo wyboru innego kszta³tu) - wadliwe
            delete aktualnyObiekt;
            aktualnyObiekt = new Linia(punktStartowy, punktKoncowy, kolor);
        }
        else if (event.type == sf::Event::MouseMoved) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && trybEdycji && obiektDoEdycji) {
                sf::Vector2i aktualnaPozycjaMyszy(event.mouseMove.x, event.mouseMove.y);
                sf::Vector2f przesuniecie = sf::Vector2f(aktualnaPozycjaMyszy - poprzedniaPozycjaMyszy);

                przesunObiekt(obiektDoEdycji, przesuniecie.x, przesuniecie.y);

                poprzedniaPozycjaMyszy = aktualnaPozycjaMyszy;
            }
        }

    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left && aktualnyObiekt) {
            punktKoncowy = Point2D(event.mouseButton.x, event.mouseButton.y);

            if (Linia* linia = dynamic_cast<Linia*>(aktualnyObiekt)) {
                linia->ustawPunkty(punktStartowy, punktKoncowy);
            }
            else if (Kolo* kolo = dynamic_cast<Kolo*>(aktualnyObiekt)) {
                float promien = std::sqrt(std::pow(punktKoncowy.x - punktStartowy.x, 2) + std::pow(punktKoncowy.y - punktStartowy.y, 2));
                kolo->ustawPunkty(punktStartowy, promien);
            }
            else if (Trojkat* trojkat = dynamic_cast<Trojkat*>(aktualnyObiekt)) {
                trojkat->ustawPunkty(punktStartowy, Point2D(event.mouseButton.x, event.mouseButton.y), Point2D(event.mouseButton.y, event.mouseButton.y));
            }
            else if (Prostokat* prostokat = dynamic_cast<Prostokat*>(aktualnyObiekt)) {
                prostokat->ustawPunkty(punktStartowy, punktKoncowy);
            }

            //Przypisanie wczytanej tekstury do nowo utworzonego obiektu
            wczytajObraz(aktualnyObiekt, sciezkaObrazu);

            //Dodanie obiektu do wektora obiekty
            obiekty.push_back(aktualnyObiekt);

            //Zresetowanie aktualnyObiekt
            aktualnyObiekt = nullptr;
        }
    }
    else if (event.type == sf::Event::MouseWheelScrolled && obiektDoEdycji) {
        //Obs³uga zoomowania obiektu w trybie edycji - nieudana

    }
    else if (event.key.code == sf::Keyboard::K) {
        std::string hexColor;

        //Utworzenie nowego okna dialogowego
        sf::RenderWindow colorPickerWindow(sf::VideoMode(500, 200), "Color Picker", sf::Style::Titlebar | sf::Style::Close);
        colorPickerWindow.setPosition(sf::Vector2i(window.getPosition().x + 50, window.getPosition().y + 50));
        colorPickerWindow.clear(sf::Color::Black);

        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Nie mo¿na za³adowaæ czcionki.\n";
            return;
        }

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(16);
        text.setPosition(10, 10);
        text.setString("Wprowadz kolor w formacie HEX (#RRGGBB):");
        text.setFillColor(sf::Color::White);

        sf::Text inputText;
        inputText.setFont(font);
        inputText.setCharacterSize(16);
        inputText.setPosition(10, 40);
        inputText.setFillColor(sf::Color::White);

        sf::Text infoText;
        infoText.setFont(font);
        infoText.setCharacterSize(16);
        infoText.setPosition(10, 70);
        infoText.setFillColor(sf::Color::White);

        bool enteringColor = true;

        while (colorPickerWindow.isOpen()) {
            sf::Event colorPickerEvent;
            while (colorPickerWindow.pollEvent(colorPickerEvent)) {
                if (colorPickerEvent.type == sf::Event::Closed) {
                    colorPickerWindow.close();
                }
                else if (colorPickerEvent.type == sf::Event::TextEntered && enteringColor) {
                    if (colorPickerEvent.text.unicode == 13) { //Enter
                        enteringColor = false;

                        if (!hexColor.empty() && hexColor[0] == '#' && hexColor.size() == 7) {
                            int r, g, b;
                            if (sscanf_s(hexColor.c_str(), "#%02x%02x%02x", &r, &g, &b) == 3) {
                                kolorWyboru = sf::Color(r, g, b);
                                infoText.setString("Kolor zmieniony!");
                            }
                            else {
                                infoText.setString("Nieprawid³owy format koloru.");
                            }
                        }
                        else {
                            infoText.setString("Nieprawid³owy format koloru.");
                        }
                    }
                    else if (colorPickerEvent.text.unicode == 8) { //Backspace
                        if (!hexColor.empty()) {
                            hexColor.pop_back();
                        }
                    }
                    else {
                        hexColor += static_cast<char>(colorPickerEvent.text.unicode);
                    }

                    inputText.setString("Wprowadzony kolor: " + hexColor);
                }
            }

            //Rysuje okno dialogowe
            colorPickerWindow.clear(sf::Color::Black);
            colorPickerWindow.draw(text);
            colorPickerWindow.draw(inputText);
            colorPickerWindow.draw(infoText);
            colorPickerWindow.display();
        }
    }
}
/**
 * @brief Metoda przesuwaj¹ca obiekt o podane przesuniêcie.
 * Wykorzystuje dynamiczne rzutowanie dla obiektów sf::Transformable.
 * @param obiekt WskaŸnik do obiektu graficznego, który ma zostaæ przesuniêty.
 * @param dx Przesuniêcie w osi X.
 * @param dy Przesuniêcie w osi Y.
 */
void Silnik::przesunObiekt(sf::Drawable* obiekt, float dx, float dy) {
    sf::Transformable* transformableObj = dynamic_cast<sf::Transformable*>(obiekt);
    if (transformableObj) {
        transformableObj->move(dx, dy);
    }
}
/**
 * @brief Metoda obracaj¹ca obiekt o podany k¹t.
 * Wykorzystuje dynamiczne rzutowanie dla obiektów sf::Transformable.
 * @param obiekt WskaŸnik do obiektu graficznego, który ma zostaæ obrócony.
 * @param kat K¹t obrotu w stopniach.
 */
void Silnik::rotujObiekt(sf::Drawable* obiekt, float kat) {
    sf::Transformable* transformableObj = dynamic_cast<sf::Transformable*>(obiekt);
    if (transformableObj) {
        transformableObj->rotate(kat);
    }
}
