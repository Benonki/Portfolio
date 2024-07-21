#pragma once
#include <SFML/Graphics.hpp>
#include "Point2D.h"

/**
 * @file Kolo.cpp
 * @brief Implementacja metod klasy Kolo.
 */
class Kolo : public sf::Drawable, public sf::Transformable {
public:
    /**
     * @brief Konstruktor tworz¹cy obiekt ko³a.
     * @param _srodek Œrodek ko³a (punkt pocz¹tkowy).
     * @param _promien Promieñ ko³a.
     * @param _kolor Kolor ko³a.
     * @param _wypelnione Okreœla, czy ko³o ma byæ wype³nione kolorem.
     */
    Kolo(Point2D _srodek, float _promien, sf::Color _kolor, bool _wypelnione);

    /**
     * @brief Metoda rysuj¹ca obiekt ko³a.
     * @param target Obiekt docelowy do rysowania.
     * @param states Kondycje rysowania.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * @brief Metoda pobieraj¹ca pozycjê œrodka ko³a.
     * @return Pozycja œrodka ko³a jako obiekt sf::Vector2f.
     */
    sf::Vector2f getPosition() const;

    /**
     * @brief Metoda ustawiaj¹ca punkty (œrodek i promieñ) ko³a.
     * @param _srodek Nowy œrodek ko³a.
     * @param _promien Nowy promieñ ko³a.
     */
    void ustawPunkty(Point2D _srodek, float _promien);

    /**
     * @brief Metoda pobieraj¹ca promieñ ko³a.
     * @return Promieñ ko³a.
     */
    float pobierzPromien() const;

    /**
     * @brief Metoda ustawiaj¹ca teksturê jako wype³nienie ko³a.
     * @param texture Tekstura do ustawienia.
     */
    void ustawWypelnienie(const sf::Texture& texture);

    /**
     * @brief Metoda pobieraj¹ca œrodek ko³a.
     * @return Pozycja œrodka ko³a jako obiekt sf::Vector2f.
     */
    sf::Vector2f pobierzSrodek() const;

    /**
     * @brief Metoda ustawiaj¹ca kolor obramowania ko³a.
     * @param color Kolor obramowania do ustawienia.
     */
    void setOutlineColor(const sf::Color& color);

private:
    Point2D srodek;         ///< Œrodek ko³a.
    float promien;          ///< Promieñ ko³a.
    sf::Color kolor;        ///< Kolor ko³a.
    bool wypelnione;        ///< Flaga okreœlaj¹ca, czy ko³o ma byæ wype³nione kolorem.
    sf::Texture texture;    ///< Tekstura jako wype³nienie ko³a.
};
