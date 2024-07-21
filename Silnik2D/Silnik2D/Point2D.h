#pragma once

/**
 * @brief Struktura reprezentuj¹ca punkt 2D o wspó³rzêdnych x i y.
 */
struct Point2D {
    float x, y; ///< Wspó³rzêdne punktu.

    /**
     * @brief Konstruktor domyœlny ustawiaj¹cy wspó³rzêdne na 0.
     */
    Point2D() : x(0.0f), y(0.0f) {}

    /**
     * @brief Konstruktor inicjalizuj¹cy wspó³rzêdne zadanymi wartoœciami.
     * @param _x Wspó³rzêdna x.
     * @param _y Wspó³rzêdna y.
     */
    Point2D(float _x, float _y) : x(_x), y(_y) {}
};
