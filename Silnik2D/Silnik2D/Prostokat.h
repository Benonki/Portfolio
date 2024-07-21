#pragma once
#include <SFML/Graphics.hpp>
#include "Point2D.h"

/**
 * @file Prostokat.cpp
 * @brief Implementacja metod klasy Prostokat.
 */
class Prostokat : public sf::Drawable, public sf::Transformable {
public:
    /**
     * @brief Konstruktor klasy Prostokat.
     * @param _punktA Punkt lewego górnego rogu prostok¹ta.
     * @param _punktB Punkt prawego dolnego rogu prostok¹ta.
     * @param _kolor Kolor prostok¹ta.
     * @param _wypelniony Flaga okreœlaj¹ca, czy prostok¹t ma byæ wype³niony kolorem.
     */
    Prostokat(Point2D _punktA, Point2D _punktB, sf::Color _kolor, bool _wypelniony);

    /**
     * @brief Funkcja rysuj¹ca prostok¹t na danym obiekcie renderuj¹cym.
     * @param target Obiekt renderuj¹cy, na którym ma zostaæ narysowany prostok¹t.
     * @param states Informacje o transformacji i stanie renderowania prostok¹ta.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * @brief Zwraca pozycjê œrodka prostok¹ta.
     * @return Pozycja œrodka prostok¹ta jako obiekt sf::Vector2f.
     */
    sf::Vector2f getPosition() const;

    /**
     * @brief Ustawia punkty prostok¹ta na podstawie dwóch przeciwnych rogów.
     * @param _punktA Punkt lewego górnego rogu prostok¹ta.
     * @param _punktB Punkt prawego dolnego rogu prostok¹ta.
     */
    void ustawPunkty(Point2D _punktA, Point2D _punktB);

    /**
     * @brief Ustawia kolor obrysu prostok¹ta.
     * @param color Kolor obrysu prostok¹ta.
     */
    void setOutlineColor(const sf::Color& color);

    /**
     * @brief Ustawia teksturê jako wype³nienie prostok¹ta.
     * @param texture Tekstura, która ma byæ u¿yta jako wype³nienie prostok¹ta.
     */
    void ustawWypelnienie(const sf::Texture& texture);

private:
    Point2D punktA; ///< Punkt lewego górnego rogu prostok¹ta.
    Point2D punktB; ///< Punkt prawego dolnego rogu prostok¹ta.
    sf::Color kolor; ///< Kolor prostok¹ta.
    bool wypelniony; ///< Flaga okreœlaj¹ca, czy prostok¹t ma byæ wype³niony kolorem.
    sf::Texture texture; ///< Tekstura u¿ywana jako wype³nienie prostok¹ta.
};
