#pragma once


enum class CellState { Empty, Ship, Hit, Miss, Bomb, hitBomb };

class Board {
public:
    Board(int x, int y, int squareSize) {}

    ~Board() {}

    void draw(RenderWindow& window, int n) {}

    bool placeShip(int row, int col) {}

    bool placeBomb(int row, int col) {}

    bool isHit(int row, int col) {}

    bool isGameOver() {}

    int m_highlightedRow;  
    int m_highlightedCol;  
    CellState** m_cells;
    float m_squareSize;
    int m_x, m_y;

};
