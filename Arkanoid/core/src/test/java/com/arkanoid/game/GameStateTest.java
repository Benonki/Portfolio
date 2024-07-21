/**
 * Klasa testująca funkcje związane z zarządzaniem stanem gry (GameState) w grze Arkanoid.
 * Testuje ustawianie różnych parametrów stanu gry oraz ich sprawdzanie.
 */
package com.arkanoid.game;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class GameStateTest {

    /**
     * Testuje ustawianie i sprawdzanie stanu gry - czy gra jest uruchomiona.
     */
    @Test
    void testSetRunning() {
        GameState.setRunning(true);
        assertTrue(GameState.isRunning());

        GameState.setRunning(false);
        assertFalse(GameState.isRunning());
    }

    /**
     * Testuje ustawianie i sprawdzanie widoczności przycisku "New Game".
     */
    @Test
    void testSetNewGameVisible() {
        GameState.setNewGameVisible(true);
        assertTrue(GameState.isNewGameVisible());

        GameState.setNewGameVisible(false);
        assertFalse(GameState.isNewGameVisible());
    }

    /**
     * Testuje ustawianie i sprawdzanie kierunku ruchu w lewo.
     */
    @Test
    void testSetWLewo() {
        GameState.setWLewo(true);
        assertTrue(GameState.isWLewo());

        GameState.setWLewo(false);
        assertFalse(GameState.isWLewo());
    }

    /**
     * Testuje ustawianie i sprawdzanie kierunku ruchu w prawo.
     */
    @Test
    void testSetWPrawo() {
        GameState.setWPrawo(true);
        assertTrue(GameState.isWPrawo());

        GameState.setWPrawo(false);
        assertFalse(GameState.isWPrawo());
    }

    /**
     * Testuje ustawianie i sprawdzanie widoczności spacji.
     */
    @Test
    void testSetSpaceVisible() {
        GameState.setSpaceVisible(true);
        assertTrue(GameState.isSpaceVisible());

        GameState.setSpaceVisible(false);
        assertFalse(GameState.isSpaceVisible());
    }

    /**
     * Testuje ustawianie i sprawdzanie statusu ukończenia poziomu.
     */
    @Test
    void testSetLevelComplete() {
        GameState.setLevelComplete(true);
        assertTrue(GameState.isLevelComplete());

        GameState.setLevelComplete(false);
        assertFalse(GameState.isLevelComplete());
    }

    /**
     * Testuje ustawianie i sprawdzanie statusu zwycięstwa.
     */
    @Test
    void testSetWinner() {
        GameState.setWinner(true);
        assertTrue(GameState.isWinner());

        GameState.setWinner(false);
        assertFalse(GameState.isWinner());
    }

    /**
     * Testuje ustawianie i sprawdzanie statusu przegranej.
     */
    @Test
    void testSetLoser() {
        GameState.setLoser(true);
        assertTrue(GameState.isLoser());

        GameState.setLoser(false);
        assertFalse(GameState.isLoser());
    }

    /**
     * Testuje ustawianie i sprawdzanie wyniku gry.
     */
    @Test
    void testSetScore() {
        int testScore = 100;
        GameState.setScore(testScore);
        assertEquals(testScore, GameState.getScore());
    }
}
