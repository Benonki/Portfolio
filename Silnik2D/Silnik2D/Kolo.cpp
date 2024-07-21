#include "Kolo.h"

/**
 * @brief Konstruktor tworz¹cy obiekt ko³a.
 * @param _srodek Œrodek ko³a (punkt pocz¹tkowy).
 * @param _promien Promieñ ko³a.
 * @param _kolor Kolor ko³a.
 * @param _wypelnione Okreœla, czy ko³o ma byæ wype³nione kolorem.
 */
Kolo::Kolo(Point2D _srodek, float _promien, sf::Color _kolor, bool _wypelnione)
    : srodek(_srodek), promien(_promien), kolor(_kolor), wypelnione(_wypelnione) {}

/**
 * @brief Metoda rysuj¹ca obiekt ko³a.
 * @param target Obiekt docelowy do rysowania.
 * @param states Kondycje rysowania.
 */
void Kolo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::CircleShape kolo(promien);
    kolo.setPosition(srodek.x - promien, srodek.y - promien);
    kolo.setFillColor(wypelnione ? kolor : sf::Color::Transparent);
    kolo.setOutlineColor(kolor);
    kolo.setOutlineThickness(1.0f);
    kolo.setTexture(&texture);
    states.transform *= getTransform();
    target.draw(kolo, states);
}

/**
 * @brief Metoda pobieraj¹ca œrodek ko³a.
 * @return Pozycja œrodka ko³a jako obiekt sf::Vector2f.
 */
sf::Vector2f Kolo::pobierzSrodek() const {
    return sf::Vector2f(srodek.x, srodek.y);
}

/**
 * @brief Metoda ustawiaj¹ca kolor obramowania ko³a.
 * @param color Kolor obramowania do ustawienia.
 */
void Kolo::setOutlineColor(const sf::Color& color) {
    kolor = color;
}

/**
 * @brief Metoda pobieraj¹ca pozycjê œrodka ko³a.
 * @return Pozycja œrodka ko³a jako obiekt sf::Vector2f.
 */
sf::Vector2f Kolo::getPosition() const {
    return sf::Vector2f(srodek.x, srodek.y);
}

/**
 * @brief Metoda ustawiaj¹ca teksturê jako wype³nienie ko³a.
 * @param texture Tekstura do ustawienia.
 */
void Kolo::ustawWypelnienie(const sf::Texture& texture) {
    this->texture = texture;
    wypelnione = true;
}

/**
 * @brief Metoda ustawiaj¹ca punkty (œrodek i promieñ) ko³a.
 * @param _srodek Nowy œrodek ko³a.
 * @param _promien Nowy promieñ ko³a.
 */
void Kolo::ustawPunkty(Point2D _srodek, float _promien) {
    srodek = _srodek;
    promien = _promien;
}

/**
 * @brief Metoda pobieraj¹ca promieñ ko³a.
 * @return Promieñ ko³a.
 */
float Kolo::pobierzPromien() const {
    return promien;
}
