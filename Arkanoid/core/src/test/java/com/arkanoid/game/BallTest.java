/**
 * Testy jednostkowe dla klasy Ball.
 */
package com.arkanoid.game;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

/**
 * Klasa testowa dla klasy Ball, skupiająca się na scenariuszach kolizji z ścianą.
 */
class BallTest {

    private Ball ball;

    /**
     * Konfiguracja obiektu Ball przed każdym testem.
     */
    @BeforeEach
    public void setUp() {
        ball = new Ball();
    }

    /**
     * Testuje metodę checkWallCollision pod kątem prawidłowego zachowania, gdy piłka uderza w ścianę.
     */
    @Test
    public void testCheckWallCollision() {
        Ball.setBallDirectionX(-1);
        Ball.setBallX(0);

        Ball.checkWallCollision();

        // Sprawdza, czy kierunek piłki zmienia się po uderzeniu w ścianę
        assertEquals(1, Ball.getBallDirectionX(), 0.001);
    }

    /**
     * Testuje metodę checkFloorCollision pod kątem prawidłowego zachowania, gdy piłka uderza w podłogę.
     */
    @Test
    public void testCheckFloorCollision() {
        Ball.setBallY(0);
        Health.setHealthCounter(3);

        Ball.checkFloorCollision();

        // Sprawdza, czy obszar staje się widoczny, a licznik zdrowia zmniejsza się po uderzeniu w podłogę
        assertEquals(true, GameState.isSpaceVisible());
        assertEquals(2, Health.getHealthCounter());
    }

    /**
     * Testuje metodę handleFloorCollision pod kątem prawidłowego zachowania, gdy piłka jest obsługiwana po uderzeniu w podłogę.
     */
    @Test
    public void testHandleFloorCollision() {
        Health.setHealthCounter(1);

        Ball.handleFloorCollision();

        // Sprawdza, czy obszar staje się widoczny, licznik zdrowia wynosi zero, a stan gry jest oznaczony jako przegrany
        assertEquals(true, GameState.isSpaceVisible());
        assertEquals(0, Health.getHealthCounter());
        assertEquals(true, GameState.isLoser());
    }
}
