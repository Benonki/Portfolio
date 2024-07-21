#pragma once //aby plik zostal skompilowany tylko raz

#include <SFML/Graphics.hpp> //dodanie biblioteki SFML odpowiadajacej za grafike
#include <iostream> //do korzystania z wejsc i wyjsc
#include <cstdlib> //do zarzadzania pamiecia w czasie dzialania programu
#include <ctime> //do pracy z czasem
#include <SFML/Audio.hpp> //dodanie biblioteki SFML odpowiadaj�cej za audio
#include "load.h" //aby znalaz� obiekty/zmienne tekstur, kt�re tu zosta�y u�yte

#define ROWS 10 //rz�dy planszy
#define COLS 10 //kolumny planszy
#define SQUARE_SIZE 50 //rozmiar pola
#define WIDTH 1150 //szeroko�� okna
#define HEIGHT 600 //wysoko�� okna

using namespace sf; //u�atwienie korzystania z bibliotek
using namespace std;

enum class CellState { Empty, Ship, Hit, Miss, Bomb, hitBomb }; //wyliczenie, kt�re u�atwi dzia�anie "switch()"

class Board { //klasa obs�uguj�ca plansze i zawieraj�ca odpowiednie metody
public:
    Board(int x, int y, int squareSize) {
        m_highlightedRow = -1; //inicjalizacja warto�ci na -1, aby wskaza�, �e �adne pole nie jest pod�wietlone
        m_highlightedCol = -1; //inicjalizacja warto�ci na -1, aby wskaza�, �e �adne pole nie jest pod�wietlone
        m_squareSize = static_cast<float>(squareSize); //jawna konwersja z int zmiennej squareSize na float i zapisanie wyniku do m_squareSize
        m_x = x; //jawna konwersja z int zmiennej x na float i zapisanie wyniku do m_x
        m_y = y; //jawna konwersja z int zmiennej y na float i zapisanie wyniku do m_y
        m_cells = new CellState * [ROWS];
        for (int i = 0; i < ROWS; i++) { //utworzenie tablicy dwuwymiarowej, kt�rej pola oznaczone s� jako "empty"; dynamicznie alokowana
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

    void draw(RenderWindow& window, int n) { //fukcja rysuj�ca plansz� w oknie z parametrem "n"
        RectangleShape square(Vector2f(m_squareSize, m_squareSize)); //inicjacja obiektu o rozmairach m_squareSize na m_squareSize
        for (int i = 0; i < ROWS; i++) { //iteracja po rz�dach tablicy dwuwymiarowej
            for (int j = 0; j < COLS; j++) { //iteracja po kolumnach tablicy dwuwymiarowej
                square.setPosition(m_x + j * m_squareSize, m_y + i * m_squareSize); //przemieszczanie obiektu odpowiednio do po�o�enia w tablicy dwuwymiarowej
                switch (m_cells[i][j]) {
                case CellState::Empty: //je�eli kom�rka ma status "Empty", to jest ustawiana tekstura "emptyTexture"
                    square.setTexture(&emptyTexture);
                    break;
                case CellState::Ship: //je�eli kom�rka ma status "Ship", to jest ustawiana tekstura "shipTexture"
                    if (n == 0) { //parametr "n" odpowiada za widoczno�� statk�w, je�eli jest r�wny 0 to wida� statki na planszy (tryb Gracz Vs Ai)
                        square.setTexture(&shipTexture);
                        break;
                    }
                    else { //je�eli "n" jest r�wne 1 lub ma inn� warto��, to ustawiana jest tekstura pustego pola (ale kom�rka ma status, �e obecny tam jest statek)
                        square.setTexture(&emptyTexture);
                        break;
                    }
                case CellState::Hit: //je�eli kom�rka ma status "Hit", to jest ustawiana tekstura "hitTexture"
                    square.setTexture(&hitTexture);
                    break;
                case CellState::Miss: //je�eli kom�rka ma status "Miss", to jest ustawiana tekstura "missTexture"
                    square.setTexture(&missTexture);
                    break;
                case CellState::Bomb: //je�eli kom�rka ma status "Bomb", to jest ustawiana tekstura "emptyTexture", aby ukry� bomby
                    square.setTexture(&emptyTexture);
                    break;
                case CellState::hitBomb: //je�eli kom�rka ma status "hitBomb", to jest ustawiana tekstura "bombTexture"
                    square.setTexture(&bombTexture);
                    break;
                }
                if (i == m_highlightedRow && j == m_highlightedCol) {  //sprawdzenie, czy pole ma by� pod�wietlone
                    square.setTexture(&highlightedTexture); //ustawienie tektury pod�wietlonego pola
                }
                window.draw(square); //wy�wietlanie ka�dego po�o�enia obiektu "square", kt�re uk�ada si� w plansz� ca�� plansz� rozgrywki
            }
        }
    }

    bool placeShip(int row, int col) { //funkcja odpowiadaj�ca za ustawiania statk�w w danym polu
        if (m_cells[row][col] != CellState::Empty) { //je�eli nie mo�na postawi� statku, zwraca false
            return false;
        }
        m_cells[row][col] = CellState::Ship; //w przeciwnym razie ustawia status "Ship" i zwraca true
        return true;
    }

    bool placeBomb(int row, int col) { //funkcja odpowiadaj�ca za ustawiania bomb w danym polu
        if (m_cells[row][col] != CellState::Empty) { //je�eli nie mo�na rozstawi� bomby, zwraca false
            return false;
        }
        m_cells[row][col] = CellState::Bomb; //w przeciwnym razie ustawia status "Bomb" i zwraca true
        return true;
    }

    bool isHit(int row, int col) { //funkcja sprawdzaj�ca trafienia
        if (m_cells[row][col] == CellState::Ship) { //je�eli trafiono statek, to kom�rka otrzymuje nowy status - "Hit"
            m_cells[row][col] = CellState::Hit;
            return true;
        }
        else if (m_cells[row][col] == CellState::Empty) { //je�eli nic w tym polu nie by�o, to oznaczamy to pole statusem "Miss"
            m_cells[row][col] = CellState::Miss;
        }
        else if (m_cells[row][col] == CellState::Bomb) { //je�eli trafiono w pole o statusie "Bomb", to kom�rka otrzymuje nowy status (hitBomb) i sprawdzamy zgodnie z dzia�aniem bomby wszystkie pola s�siaduj�ce z bomb�
            m_cells[row][col] = CellState::hitBomb;
            bool hit = false; //dodatkowa zmienna, kt�ra b�dzie przechowywa� informacj� o trafieniu statku w obszarze bomby

            for (int i = -1; i <= 1; i++) { //funkcja sprawdzaj�ca trafienia s�siaduj�cych p�l i wywo�uj�ca rekurencyjnie funkcj� "isHit"
                for (int j = -1; j <= 1; j++) {
                    int newRow = row + i;
                    int newCol = col + j;
                    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
                        if (isHit(newRow, newCol)) { //rekurencyjne wywo�anie funkcji "isHit"
                            hit = true; //Je�li kt�re� wywo�anie zwr�ci�o true, ustawiamy hit na true
                        }
                    }
                }
            }
            return hit; //zwracamy warto�� hit po zako�czeniu p�tli

        }
        return false; //zwracamy false, gdy nic nie trafiono lub bomba nic nie trafi�a
    }


    bool isGameOver() { //funkcja sprawdzaj�ca stan gry - je�eli w tablicy dwuwymiarowej nie ma ju� kom�rek ze statusem "Ship" to zwraca true
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (m_cells[i][j] == CellState::Ship) {
                    return false;
                }
            }
        }
        return true;
    }

    int m_highlightedRow; //wiersz pod�wietlonego pola
    int m_highlightedCol; //kolumna pod�wietlonego pola
    CellState** m_cells; //deklaracja zmiennej m_cells typu wska�nik na wska�nik do obiekt�w typu CellState
    float m_squareSize; //deklaracja zmiennej m_squareSize typu float
    int m_x, m_y; //deklaracja zmiennych m_x oraz m_y typu int
};