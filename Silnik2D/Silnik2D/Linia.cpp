/**
 * @file Linia.cpp
 * @brief Implementacja metod klasy Linia.
 */

#include "Linia.h"

 /**
  * @brief Konstruktor klasy Linia.
  * @param _punktPoczatkowy Punkt pocz¹tkowy linii.
  * @param _punktKoncowy Punkt koñcowy linii.
  * @param _kolor Kolor linii.
  */
Linia::Linia(Point2D _punktPoczatkowy, Point2D _punktKoncowy, sf::Color _kolor)
    : punktPoczatkowy(_punktPoczatkowy), punktKoncowy(_punktKoncowy), kolor(_kolor) {}

/**
 * @brief Metoda rysuj¹ca liniê na docelowym obiekcie renderuj¹cym.
 * @param target Obiekt renderuj¹cy, na którym rysowaæ.
 * @param states Stany renderowania do zastosowania.
 */
void Linia::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Tworzenie linii za pomoc¹ dwóch wierzcho³ków
    sf::Vertex linia[] = {
        sf::Vertex(sf::Vector2f(punktPoczatkowy.x, punktPoczatkowy.y), kolor),
        sf::Vertex(sf::Vector2f(punktKoncowy.x, punktKoncowy.y), kolor)
    };

    // Zastosowanie transformacji obiektu
    states.transform *= getTransform();
    target.draw(linia, 2, sf::Lines, states);
}

/**
 * @brief Pobranie pozycji œrodkowego punktu linii.
 * @return Pozycja œrodkowego punktu linii.
 */
sf::Vector2f Linia::getPosition() const {
    return sf::Vector2f((punktPoczatkowy.x + punktKoncowy.x) / 2, (punktPoczatkowy.y + punktKoncowy.y) / 2);
}

/**
 * @brief Ustawienie punktów pocz¹tkowego i koñcowego linii.
 * @param _punktPoczatkowy Punkt pocz¹tkowy linii.
 * @param _punktKoncowy Punkt koñcowy linii.
 */
void Linia::ustawPunkty(Point2D _punktPoczatkowy, Point2D _punktKoncowy) {
    punktPoczatkowy = _punktPoczatkowy;
    punktKoncowy = _punktKoncowy;
}
