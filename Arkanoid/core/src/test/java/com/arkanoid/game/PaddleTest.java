/**
 * Klasa testująca funkcje związane z paletką (Paddle) w grze Arkanoid.
 * Testuje kolizję z piłką, ruch w prawo, ruch w lewo, stan trafienia, ustawianie prędkości, oraz ustawianie pozycji paletki.
 */
package com.arkanoid.game;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class PaddleTest {

    /**
     * Testuje kolizję paletki z piłką i sprawdza, czy piłka zmienia kierunek ruchu pionowego po kolizji.
     */
    @Test
    void testCheckCollisionWithBall() {
        // Ustawienie piłki w centrum paletki
        Ball.setBallX(Paddle.getPaddleX() + Paddle.paddleWidth / 2);
        Ball.setBallY(Paddle.getPaddleY() + Paddle.paddleHeight / 2);

        // Sprawdzenie kolizji i zmiany kierunku piłki w górę
        Paddle.checkCollisionWithBall();
        assertTrue(Ball.getBallDirectionY() > 0);
    }

    /**
     * Testuje ruch paletki w prawo i sprawdza, czy pozycja paletki jest większa niż początkowa.
     */
    @Test
    void testMoveRight() {
        // Zapisanie początkowej pozycji paletki
        float initialX = Paddle.getPaddleX();

        // Wywołanie metody ruchu w prawo i sprawdzenie, czy nowa pozycja jest większa niż początkowa
        Paddle.moveRight();
        assertTrue(Paddle.getPaddleX() > initialX);
    }

    /**
     * Testuje ruch paletki w lewo i sprawdza, czy pozycja paletki jest mniejsza niż początkowa.
     */
    @Test
    void testMoveLeft() {
        // Zapisanie początkowej pozycji paletki
        float initialX = Paddle.getPaddleX();

        // Wywołanie metody ruchu w lewo i sprawdzenie, czy nowa pozycja jest mniejsza niż początkowa
        Paddle.moveLeft();
        assertTrue(Paddle.getPaddleX() < initialX);
    }

    /**
     * Testuje stan trafienia paletki i sprawdza, czy wartość jest poprawnie ustawiana i odczytywana.
     */
    @Test
    void testIsPaddleHit() {
        // Sprawdzenie początkowego stanu trafienia (niepowiązanego z kolizją)
        assertFalse(Paddle.isPaddleHit());

        // Ustawienie trafienia i sprawdzenie, czy wartość została poprawnie ustawiona
        Paddle.setPaddleHit(true);
        assertTrue(Paddle.isPaddleHit());
    }

    /**
     * Testuje ustawianie prędkości paletki i sprawdza, czy wartość prędkości jest poprawnie ustawiana i odczytywana.
     */
    @Test
    void testSetPaddleSpeed() {
        // Ustawienie prędkości paletki
        Paddle.setPaddleSpeed(15f);

        // Sprawdzenie, czy wartość prędkości została poprawnie ustawiona
        assertEquals(15f, Paddle.getPaddleSpeed(), 0.001);
    }

    /**
     * Testuje ustawianie pozycji paletki i sprawdza, czy wartość pozycji jest poprawnie ustawiana i odczytywana.
     */
    @Test
    void testSetPaddleX() {
        // Ustawienie nowej pozycji paletki
        Paddle.setPaddleX(50f);

        // Sprawdzenie, czy wartość pozycji została poprawnie ustawiona
        assertEquals(50f, Paddle.getPaddleX(), 0.001);
    }
}
