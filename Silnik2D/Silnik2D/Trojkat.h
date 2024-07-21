#pragma once
#include <SFML/Graphics.hpp>
#include "Point2D.h"

/**
 * @file Trojkat.cpp
 * @brief Implementacja metod klasy Trojkat.
 */
class Trojkat : public sf::Drawable, public sf::Transformable {
public:
    /**
     * @brief Konstruktor klasy Trojkat.
     * @param _punktA Punkt pierwszego wierzcho³ka trójk¹ta.
     * @param _punktB Punkt drugiego wierzcho³ka trójk¹ta.
     * @param _punktC Punkt trzeciego wierzcho³ka trójk¹ta.
     * @param _kolor Kolor trójk¹ta.
     * @param _wypelniony Flaga okreœlaj¹ca, czy trójk¹t ma byæ wype³niony kolorem.
     */
    Trojkat(Point2D _punktA, Point2D _punktB, Point2D _punktC, sf::Color _kolor, bool _wypelniony);

    /**
     * @brief Funkcja rysuj¹ca trójk¹t na danym obiekcie renderuj¹cym.
     * @param target Obiekt renderuj¹cy, na którym ma zostaæ narysowany trójk¹t.
     * @param states Informacje o transformacji i stanie renderowania trójk¹ta.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * @brief Zwraca pozycjê œrodka trójk¹ta.
     * @return Pozycja œrodka trójk¹ta jako obiekt sf::Vector2f.
     */
    sf::Vector2f getPosition() const;

    /**
     * @brief Ustawia wierzcho³ki trójk¹ta na podstawie trzech punktów.
     * @param _punktA Punkt pierwszego wierzcho³ka trójk¹ta.
     * @param _punktB Punkt drugiego wierzcho³ka trójk¹ta.
     * @param _punktC Punkt trzeciego wierzcho³ka trójk¹ta.
     */
    void ustawPunkty(Point2D _punktA, Point2D _punktB, Point2D _punktC);

    /**
     * @brief Ustawia kolor obrysu trójk¹ta.
     * @param color Kolor obrysu trójk¹ta.
     */
    void setOutlineColor(const sf::Color& color);

    /**
     * @brief Ustawia teksturê jako wype³nienie trójk¹ta.
     * @param texture Tekstura, która ma byæ u¿yta jako wype³nienie trójk¹ta.
     */
    void ustawWypelnienie(const sf::Texture& texture);

private:
    Point2D punktA; ///< Punkt pierwszego wierzcho³ka trójk¹ta.
    Point2D punktB; ///< Punkt drugiego wierzcho³ka trójk¹ta.
    Point2D punktC; ///< Punkt trzeciego wierzcho³ka trójk¹ta.
    sf::Color kolor; ///< Kolor trójk¹ta.
    bool wypelniony; ///< Flaga okreœlaj¹ca, czy trójk¹t ma byæ wype³niony kolorem.
    sf::Texture texture; ///< Tekstura u¿ywana jako wype³nienie trójk¹ta.
};
