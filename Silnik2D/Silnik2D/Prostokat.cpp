#include "Prostokat.h"

/**
 * @brief Konstruktor klasy Prostokat.
 * @param _punktA Punkt lewego górnego rogu prostok¹ta.
 * @param _punktB Punkt prawego dolnego rogu prostok¹ta.
 * @param _kolor Kolor prostok¹ta.
 * @param _wypelniony Flaga okreœlaj¹ca, czy prostok¹t ma byæ wype³niony kolorem.
 */
Prostokat::Prostokat(Point2D _punktA, Point2D _punktB, sf::Color _kolor, bool _wypelniony)
    : punktA(_punktA), punktB(_punktB), kolor(_kolor), wypelniony(_wypelniony) {}

/**
 * @brief Funkcja rysuj¹ca prostok¹t na danym obiekcie renderuj¹cym.
 * @param target Obiekt renderuj¹cy, na którym ma zostaæ narysowany prostok¹t.
 * @param states Informacje o transformacji i stanie renderowania prostok¹ta.
 */
void Prostokat::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape prostokat(sf::Vector2f(std::abs(punktB.x - punktA.x), std::abs(punktB.y - punktA.y)));
    prostokat.setPosition(std::min(punktA.x, punktB.x), std::min(punktA.y, punktB.y));
    prostokat.setFillColor(wypelniony ? kolor : sf::Color::Transparent);
    prostokat.setOutlineColor(kolor);
    prostokat.setOutlineThickness(1.0f);
    prostokat.setTexture(&texture);
    states.transform *= getTransform();
    target.draw(prostokat, states);
}

/**
 * @brief Zwraca pozycjê œrodka prostok¹ta.
 * @return Pozycja œrodka prostok¹ta jako obiekt sf::Vector2f.
 */
sf::Vector2f Prostokat::getPosition() const {
    return sf::Vector2f((punktA.x + punktB.x) / 2, (punktA.y + punktB.y) / 2);
}

/**
 * @brief Ustawia punkty prostok¹ta na podstawie dwóch przeciwnych rogów.
 * @param _punktA Punkt lewego górnego rogu prostok¹ta.
 * @param _punktB Punkt prawego dolnego rogu prostok¹ta.
 */
void Prostokat::ustawPunkty(Point2D _punktA, Point2D _punktB) {
    punktA = _punktA;
    punktB = _punktB;
}

/**
 * @brief Ustawia kolor obrysu prostok¹ta.
 * @param color Kolor obrysu prostok¹ta.
 */
void Prostokat::setOutlineColor(const sf::Color& color) {
    kolor = color;
}

/**
 * @brief Ustawia teksturê jako wype³nienie prostok¹ta.
 * @param texture Tekstura, która ma byæ u¿yta jako wype³nienie prostok¹ta.
 */
void Prostokat::ustawWypelnienie(const sf::Texture& texture) {
    this->texture = texture;
    wypelniony = true;
}
