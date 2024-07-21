#include "board.h"
#include "Gra w Statki.cpp"

class Board {
public:
    Board(int x, int y, int squareSize) {
        m_highlightedRow = -1;  // Inicjalizacja wartoœci na -1, aby wskazaæ, ¿e ¿adne pole nie jest podœwietlone
        m_highlightedCol = -1;
        m_squareSize = static_cast<float>(squareSize);
        m_x = x;
        m_y = y;
        m_cells = new CellState * [ROWS];
        for (int i = 0; i < ROWS; i++) { //utworzenie pustej tablicy dwuwymiarowej
            m_cells[i] = new CellState[COLS];
            for (int j = 0; j < COLS; j++) {
                m_cells[i][j] = CellState::Empty;
            }
        }
    }

    ~Board() {
        for (int i = 0; i < ROWS; i++) {
            delete[] m_cells[i];
        }
        delete[] m_cells;
    }

    void draw(RenderWindow& window, int n) {
        RectangleShape square(Vector2f(m_squareSize, m_squareSize));
        for (int i = 0; i < ROWS; i++) { //okreslanie i rysowanie pol o odpowiednich kolorach
            for (int j = 0; j < COLS; j++) {
                square.setPosition(m_x + j * m_squareSize, m_y + i * m_squareSize);
                switch (m_cells[i][j]) {
                case CellState::Empty:
                    square.setTexture(&emptyTexture);
                    window.draw(square);
                    break;
                case CellState::Ship:
                    if (n == 0) {
                        square.setTexture(&shipTexture);
                        window.draw(square);
                        break;
                    }
                    else {
                        square.setTexture(&emptyTexture);
                        window.draw(square);
                        break;
                    }
                case CellState::Hit:
                    square.setTexture(&hitTexture);
                    window.draw(square);
                    break;
                case CellState::Miss:
                    square.setTexture(&missTexture);
                    window.draw(square);
                    break;
                case CellState::Bomb:
                    square.setTexture(&bombTexture);
                    window.draw(square);
                    break;
                case CellState::hitBomb:
                    square.setTexture(&bombTexture);
                    window.draw(square);
                    break;
                }
                if (i == m_highlightedRow && j == m_highlightedCol) {  // Sprawdzenie, czy pole jest podœwietlone
                    square.setTexture(&highlightedTexture); // Ustawienie koloru podœwietlonego pola (mo¿esz zmieniæ na inny kolor, jeœli chcesz)
                    window.draw(square);
                }
                window.draw(square);
            }
        }
    }

    bool placeShip(int row, int col) {
        if (m_cells[row][col] != CellState::Empty) {
            return false;
        }
        m_cells[row][col] = CellState::Ship;
        return true;
    }

    bool placeBomb(int row, int col) {
        if (m_cells[row][col] != CellState::Empty) {
            return false;
        }
        m_cells[row][col] = CellState::Bomb;
        return true;
    }

    bool isHit(int row, int col) {
        if (m_cells[row][col] == CellState::Ship) {
            m_cells[row][col] = CellState::Hit;
            return true;
        }
        else if (m_cells[row][col] == CellState::Empty) {
            m_cells[row][col] = CellState::Miss;
        }
        else if (m_cells[row][col] == CellState::Bomb) {
            m_cells[row][col] = CellState::hitBomb;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int newRow = row + i;
                    int newCol = col + j;
                    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
                        isHit(newRow, newCol);
                    }
                }
            }
        }
        return false;
    }

    bool isGameOver() {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (m_cells[i][j] == CellState::Ship) {
                    return false;
                }
            }
        }
        return true;
    }
};