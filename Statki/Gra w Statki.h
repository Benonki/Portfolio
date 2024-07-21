#pragma once //aby plik zostal skompilowany tylko raz

#include <SFML/Graphics.hpp> //dodanie biblioteki SFML odpowiadajacej za grafike
#include <iostream> //do korzystania z wejsc i wyjsc
#include <cstdlib> //do zarzadzania pamiecia w czasie dzialania programu
#include <ctime> //do pracy z czasem
#include <SFML/Audio.hpp> //dodanie biblioteki SFML odpowiadaj¹cej za audio
#include "load.h" //aby znalaz³ obiekty/zmienne tekstur, które tu zosta³y u¿yte

#define ROWS 10 //rzêdy planszy
#define COLS 10 //kolumny planszy
#define SQUARE_SIZE 50 //rozmiar pola
#define WIDTH 1150 //szerokoœæ okna
#define HEIGHT 600 //wysokoœæ okna

using namespace sf; //u³atwienie korzystania z bibliotek
using namespace std;

enum class CellState { Empty, Ship, Hit, Miss, Bomb, hitBomb }; //wyliczenie, które u³atwi dzia³anie "switch()"

class Board { //klasa obs³uguj¹ca plansze i zawieraj¹ca odpowiednie metody
public:
    Board(int x, int y, int squareSize) {
        m_highlightedRow = -1; //inicjalizacja wartoœci na -1, aby wskazaæ, ¿e ¿adne pole nie jest podœwietlone
        m_highlightedCol = -1; //inicjalizacja wartoœci na -1, aby wskazaæ, ¿e ¿adne pole nie jest podœwietlone
        m_squareSize = static_cast<float>(squareSize); //jawna konwersja z int zmiennej squareSize na float i zapisanie wyniku do m_squareSize
        m_x = x; //jawna konwersja z int zmiennej x na float i zapisanie wyniku do m_x
        m_y = y; //jawna konwersja z int zmiennej y na float i zapisanie wyniku do m_y
        m_cells = new CellState * [ROWS];
        for (int i = 0; i < ROWS; i++) { //utworzenie tablicy dwuwymiarowej, której pola oznaczone s¹ jako "empty"; dynamicznie alokowana
            m_cells[i] = new CellState[COLS];
            for (int j = 0; j < COLS; j++) {
                m_cells[i][j] = CellState::Empty;
            }
        }
    }

    ~Board() { //destruktor klasy Board; zwalnia pamiec
        for (int i = 0; i < ROWS; i++) {
            delete[] m_cells[i];
        }
        delete[] m_cells;
    }

    void draw(RenderWindow& window, int n) { //fukcja rysuj¹ca planszê w oknie z parametrem "n"
        RectangleShape square(Vector2f(m_squareSize, m_squareSize)); //inicjacja obiektu o rozmairach m_squareSize na m_squareSize
        for (int i = 0; i < ROWS; i++) { //iteracja po rzêdach tablicy dwuwymiarowej
            for (int j = 0; j < COLS; j++) { //iteracja po kolumnach tablicy dwuwymiarowej
                square.setPosition(m_x + j * m_squareSize, m_y + i * m_squareSize); //przemieszczanie obiektu odpowiednio do po³o¿enia w tablicy dwuwymiarowej
                switch (m_cells[i][j]) {
                case CellState::Empty: //je¿eli komórka ma status "Empty", to jest ustawiana tekstura "emptyTexture"
                    square.setTexture(&emptyTexture);
                    break;
                case CellState::Ship: //je¿eli komórka ma status "Ship", to jest ustawiana tekstura "shipTexture"
                    if (n == 0) { //parametr "n" odpowiada za widocznoœæ statków, je¿eli jest równy 0 to widaæ statki na planszy (tryb Gracz Vs Ai)
                        square.setTexture(&shipTexture);
                        break;
                    }
                    else { //je¿eli "n" jest równe 1 lub ma inn¹ wartoœæ, to ustawiana jest tekstura pustego pola (ale komórka ma status, ¿e obecny tam jest statek)
                        square.setTexture(&emptyTexture);
                        break;
                    }
                case CellState::Hit: //je¿eli komórka ma status "Hit", to jest ustawiana tekstura "hitTexture"
                    square.setTexture(&hitTexture);
                    break;
                case CellState::Miss: //je¿eli komórka ma status "Miss", to jest ustawiana tekstura "missTexture"
                    square.setTexture(&missTexture);
                    break;
                case CellState::Bomb: //je¿eli komórka ma status "Bomb", to jest ustawiana tekstura "emptyTexture", aby ukryæ bomby
                    square.setTexture(&emptyTexture);
                    break;
                case CellState::hitBomb: //je¿eli komórka ma status "hitBomb", to jest ustawiana tekstura "bombTexture"
                    square.setTexture(&bombTexture);
                    break;
                }
                if (i == m_highlightedRow && j == m_highlightedCol) {  //sprawdzenie, czy pole ma byæ podœwietlone
                    square.setTexture(&highlightedTexture); //ustawienie tektury podœwietlonego pola
                }
                window.draw(square); //wyœwietlanie ka¿dego po³o¿enia obiektu "square", które uk³ada siê w planszê ca³¹ planszê rozgrywki
            }
        }
    }

    bool placeShip(int row, int col) { //funkcja odpowiadaj¹ca za ustawiania statków w danym polu
        if (m_cells[row][col] != CellState::Empty) { //je¿eli nie mo¿na postawiæ statku, zwraca false
            return false;
        }
        m_cells[row][col] = CellState::Ship; //w przeciwnym razie ustawia status "Ship" i zwraca true
        return true;
    }

    bool placeBomb(int row, int col) { //funkcja odpowiadaj¹ca za ustawiania bomb w danym polu
        if (m_cells[row][col] != CellState::Empty) { //je¿eli nie mo¿na rozstawiæ bomby, zwraca false
            return false;
        }
        m_cells[row][col] = CellState::Bomb; //w przeciwnym razie ustawia status "Bomb" i zwraca true
        return true;
    }

    bool isHit(int row, int col) { //funkcja sprawdzaj¹ca trafienia
        if (m_cells[row][col] == CellState::Ship) { //je¿eli trafiono statek, to komórka otrzymuje nowy status - "Hit"
            m_cells[row][col] = CellState::Hit;
            return true;
        }
        else if (m_cells[row][col] == CellState::Empty) { //je¿eli nic w tym polu nie by³o, to oznaczamy to pole statusem "Miss"
            m_cells[row][col] = CellState::Miss;
        }
        else if (m_cells[row][col] == CellState::Bomb) { //je¿eli trafiono w pole o statusie "Bomb", to komórka otrzymuje nowy status (hitBomb) i sprawdzamy zgodnie z dzia³aniem bomby wszystkie pola s¹siaduj¹ce z bomb¹
            m_cells[row][col] = CellState::hitBomb;
            bool hit = false; //dodatkowa zmienna, która bêdzie przechowywaæ informacjê o trafieniu statku w obszarze bomby

            for (int i = -1; i <= 1; i++) { //funkcja sprawdzaj¹ca trafienia s¹siaduj¹cych pól i wywo³uj¹ca rekurencyjnie funkcjê "isHit"
                for (int j = -1; j <= 1; j++) {
                    int newRow = row + i;
                    int newCol = col + j;
                    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
                        if (isHit(newRow, newCol)) { //rekurencyjne wywo³anie funkcji "isHit"
                            hit = true; //Jeœli któreœ wywo³anie zwróci³o true, ustawiamy hit na true
                        }
                    }
                }
            }
            return hit; //zwracamy wartoœæ hit po zakoñczeniu pêtli

        }
        return false; //zwracamy false, gdy nic nie trafiono lub bomba nic nie trafi³a
    }


    bool isGameOver() { //funkcja sprawdzaj¹ca stan gry - je¿eli w tablicy dwuwymiarowej nie ma ju¿ komórek ze statusem "Ship" to zwraca true
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (m_cells[i][j] == CellState::Ship) {
                    return false;
                }
            }
        }
        return true;
    }

    int m_highlightedRow; //wiersz podœwietlonego pola
    int m_highlightedCol; //kolumna podœwietlonego pola
    CellState** m_cells; //deklaracja zmiennej m_cells typu wskaŸnik na wskaŸnik do obiektów typu CellState
    float m_squareSize; //deklaracja zmiennej m_squareSize typu float
    int m_x, m_y; //deklaracja zmiennych m_x oraz m_y typu int
};