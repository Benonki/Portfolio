/**
 * Klasa testująca funkcjonalności związane z blokami w grze Arkanoid.
 * Testuje tworzenie bloków, obsługę kolizji z piłką oraz pobieranie liczby wierszy i kolumn.
 */
package com.arkanoid.game;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class BlockTest {
    private Block block;

    /**
     * Testuje tworzenie bloków o różnych typach.
     * Sprawdza, czy liczba wierszy i kolumn jest poprawna dla każdego typu bloku.
     */
    @Test
    void testCreateBlocks() {
        Block block = new Block(1);
        assertEquals(3, Block.getNumberOfRows());
        assertEquals(9, Block.getNumberOfColumns());

        block = new Block(2);
        assertEquals(4, Block.getNumberOfRows());
        assertEquals(9, Block.getNumberOfColumns());
    }

    /**
     * Testuje obsługę kolizji bloku z piłką.
     * Sprawdza, czy po kolizji liczba bloków zmniejsza się o 1, a wynik gry zwiększa się o 10 punktów.
     */
    @Test
    public void testHandleCollisionWithBall() {
        Block block = new Block(1);
        Ball.setBallX(Block.startX);
        Ball.setBallY(Block.startY - 1);
        int initialBlockCount = block.getBlocks().size;

        block.handleCollisionWithBall();

        assertEquals(initialBlockCount - 1, block.getBlocks().size);
        assertEquals(10, GameState.getScore());
    }

    /**
     * Testuje pobieranie liczby wierszy bloków.
     * Sprawdza, czy początkowa liczba wierszy jest poprawna, a następnie zmienia i sprawdza ponownie.
     */
    @Test
    public void testGetNumberOfRows() {
        Block block = new Block(1);
        assertEquals(3, Block.getNumberOfRows());
        Block.setNumberOfRows(5);
        assertEquals(5, Block.getNumberOfRows());
    }

    /**
     * Testuje pobieranie liczby kolumn bloków.
     * Sprawdza, czy początkowa liczba kolumn jest poprawna, a następnie zmienia i sprawdza ponownie.
     */
    @Test
    public void testGetNumberOfColumns() {
        assertEquals(9, Block.getNumberOfColumns());

        Block.setNumberOfColumns(7);
        assertEquals(7, Block.getNumberOfColumns());
    }
}
