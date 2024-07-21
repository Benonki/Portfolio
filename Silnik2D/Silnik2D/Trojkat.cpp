#include "Trojkat.h"

/**
 * @brief Konstruktor klasy Trojkat.
 * @param _punktA Punkt pierwszego wierzcho³ka trójk¹ta.
 * @param _punktB Punkt drugiego wierzcho³ka trójk¹ta.
 * @param _punktC Punkt trzeciego wierzcho³ka trójk¹ta.
 * @param _kolor Kolor trójk¹ta.
 * @param _wypelniony Flaga okreœlaj¹ca, czy trójk¹t ma byæ wype³niony kolorem.
 */
Trojkat::Trojkat(Point2D _punktA, Point2D _punktB, Point2D _punktC, sf::Color _kolor, bool _wypelniony)
    : punktA(_punktA), punktB(_punktB), punktC(_punktC), kolor(_kolor), wypelniony(_wypelniony) {}

/**
 * @brief Funkcja rysuj¹ca trójk¹t na danym obiekcie renderuj¹cym.
 * @param target Obiekt renderuj¹cy, na którym ma zostaæ narysowany trójk¹t.
 * @param states Informacje o transformacji i stanie renderowania trójk¹ta.
 */
void Trojkat::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::ConvexShape trojkat(3);
    trojkat.setPoint(0, sf::Vector2f(punktA.x, punktA.y));
    trojkat.setPoint(1, sf::Vector2f(punktB.x, punktB.y));
    trojkat.setPoint(2, sf::Vector2f(punktC.x, punktC.y));
    trojkat.setFillColor(wypelniony ? kolor : sf::Color::Transparent);
    trojkat.setOutlineColor(kolor);
    trojkat.setOutlineThickness(1.0f);
    trojkat.setTexture(&texture);
    states.transform *= getTransform();
    target.draw(trojkat, states);
}

/**
 * @brief Zwraca pozycjê œrodka trójk¹ta.
 * @return Pozycja œrodka trójk¹ta jako obiekt sf::Vector2f.
 */
sf::Vector2f Trojkat::getPosition() const {
    return sf::Vector2f((punktA.x + punktB.x + punktC.x) / 3, (punktA.y + punktB.y + punktC.y) / 3);
}

/**
 * @brief Ustawia wierzcho³ki trójk¹ta na podstawie trzech punktów.
 * @param _punktA Punkt pierwszego wierzcho³ka trójk¹ta.
 * @param _punktB Punkt drugiego wierzcho³ka trójk¹ta.
 * @param _punktC Punkt trzeciego wierzcho³ka trójk¹ta.
 */
void Trojkat::ustawPunkty(Point2D _punktA, Point2D _punktB, Point2D _punktC) {
    punktA = _punktA;
    punktB = _punktB;
    punktC = _punktC;
}

/**
 * @brief Ustawia kolor obrysu trójk¹ta.
 * @param color Kolor obrysu trójk¹ta.
 */
void Trojkat::setOutlineColor(const sf::Color& color) {
    kolor = color;
}

/**
 * @brief Ustawia teksturê jako wype³nienie trójk¹ta.
 * @param texture Tekstura, która ma byæ u¿yta jako wype³nienie trójk¹ta.
 */
void Trojkat::ustawWypelnienie(const sf::Texture& texture) {
    this->texture = texture;
    wypelniony = true;
}
