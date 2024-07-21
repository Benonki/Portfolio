#pragma once
#include <SFML/Graphics.hpp>
#include "Point2D.h"

/**
 * @brief Klasa reprezentuj¹ca obiekt linii w przestrzeni 2D.
 */
class Linia : public sf::Drawable, public sf::Transformable {
public:
    /**
     * @brief Konstruktor inicjalizuj¹cy obiekt linii.
     * @param _punktPoczatkowy Pocz¹tkowy punkt linii.
     * @param _punktKoncowy Koñcowy punkt linii.
     * @param _kolor Kolor linii.
     */
    Linia(Point2D _punktPoczatkowy, Point2D _punktKoncowy, sf::Color _kolor);

    /**
     * @brief Metoda rysuj¹ca obiekt linii.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * @brief Metoda zwracaj¹ca pozycjê œrodka linii.
     */
    sf::Vector2f getPosition() const;

    /**
     * @brief Metoda ustawiaj¹ca punkty pocz¹tkowy i koñcowy linii.
     * @param _punktPoczatkowy Nowy punkt pocz¹tkowy linii.
     * @param _punktKoncowy Nowy punkt koñcowy linii.
     */
    void ustawPunkty(Point2D _punktPoczatkowy, Point2D _punktKoncowy);

private:
    Point2D punktPoczatkowy; /**< Pocz¹tkowy punkt linii. */
    Point2D punktKoncowy;    /**< Koñcowy punkt linii. */
    sf::Color kolor;         /**< Kolor linii. */
};
