#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Point2D.h"
#include "Linia.h"
#include "Kolo.h"
#include "Trojkat.h"
#include "Prostokat.h"

/**
 * @file Silnik.cpp
 * @brief Klasa Silnik odpowiada za zarz¹dzanie g³ówn¹ logik¹ programu.
 */
class Silnik {
public:
    /**
     * @brief Konstruktor klasy Silnik.
     */
    Silnik();

    /**
     * @brief Destruktor klasy Silnik.
     */
    ~Silnik();

    /**
     * @brief Metoda uruchamiaj¹ca g³ówn¹ pêtlê programu.
     */
    void uruchom();

private:
    sf::RenderTexture renderTexture; ///< Tekstura u¿ywana do renderowania obiektów.
    sf::RenderWindow window; ///< Okno g³ówne programu.
    std::vector<sf::Drawable*> obiekty; ///< Wektor przechowuj¹cy wskaŸniki do rysowalnych obiektów.
    sf::Drawable* aktualnyObiekt; ///< WskaŸnik do aktualnie rysowanego obiektu.
    bool czyWypelnione; ///< Flaga okreœlaj¹ca, czy obiekt ma byæ wype³niony kolorem.
    sf::Color kolor; ///< Kolor aktualnie rysowanego obiektu.
    Point2D punktStartowy; ///< Punkt pocz¹tkowy dla rysowanego obiektu.
    Point2D punktKoncowy; ///< Punkt koñcowy dla rysowanego obiektu.
    Point2D punktA, punktB, punktC; ///< Punkty pomocnicze dla niektórych obiektów.
    float promien; ///< Promieñ u¿ywany dla okrêgów.
    bool trybEdycji; ///< Flaga okreœlaj¹ca, czy program dzia³a w trybie edycji.
    sf::Color kolorEdycji; ///< Kolor zaznaczenia w trybie edycji.
    sf::Drawable* obiektDoEdycji; ///< WskaŸnik do obiektu podlegaj¹cego edycji.
    sf::Vector2i poprzedniaPozycjaMyszy; ///< Poprzednia pozycja myszy, u¿ywana do przesuwania obiektów.
    bool czyZaznaczony; ///< Flaga okreœlaj¹ca, czy obiekt jest zaznaczony w trybie edycji.
    float katObracaniaZaznaczenia; ///< K¹t obrotu zaznaczonego obiektu.
    bool wybieranieKoloru; ///< Flaga okreœlaj¹ca, czy u¿ytkownik wybiera kolor.
    sf::Color kolorWyboru; ///< Kolor wybrany przez u¿ytkownika.
    std::string sciezkaObrazu; ///< Œcie¿ka do wczytywanego obrazu.

    /**
     * @brief Metoda odpowiedzialna za rysowanie wszystkich obiektów na renderTexture.
     */
    void rysujObiekty();

    /**
     * @brief Metoda obs³uguj¹ca zdarzenia generowane przez u¿ytkownika.
     * @param event Zdarzenie SFML.
     */
    void obslugaZdarzen(const sf::Event& event);

    /**
     * @brief Metoda przesuwaj¹ca obiekt o zadane wartoœci dx i dy.
     * @param obiekt WskaŸnik do rysowalnego obiektu.
     * @param dx Przesuniêcie w osi X.
     * @param dy Przesuniêcie w osi Y.
     */
    void przesunObiekt(sf::Drawable* obiekt, float dx, float dy);

    /**
     * @brief Metoda obracaj¹ca obiekt o zadany k¹t.
     * @param obiekt WskaŸnik do rysowalnego obiektu.
     * @param kat K¹t obrotu.
     */
    void rotujObiekt(sf::Drawable* obiekt, float kat);

    /**
     * @brief Metoda wczytuj¹ca obraz do obiektu, je¿eli jest to mo¿liwe (obiekt wype³nialny).
     * @param obiekt WskaŸnik do rysowalnego obiektu.
     * @param sciezkaObrazu Œcie¿ka do wczytywanego obrazu.
     */
    void wczytajObraz(sf::Drawable* obiekt, const std::string& sciezkaObrazu);
};
