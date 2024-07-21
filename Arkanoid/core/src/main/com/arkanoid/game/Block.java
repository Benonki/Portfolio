package com.arkanoid.game;

import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.utils.Array;
import java.util.Iterator;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

/**
 * Klasa reprezentująca bloki w grze typu Arkanoid.
 * Zawiera metody do tworzenia, rysowania i obsługi kolizji z blokami.
 */
public class Block {
    /**
     * Lista prostokątów reprezentujących bloki.
     */
    private Array<Rectangle> blocks;

    /**
     * Liczba wierszy bloków.
     */
    private static int numberOfRows;

    /**
     * Liczba kolumn bloków.
     */
    private static int numberOfColumns;

    /**
     * Szerokość pojedynczego bloku.
     */
    public static final float blockWidth = 55;

    /**
     * Wysokość pojedynczego bloku.
     */
    public static final float blockHeight = 20;

    /**
     * Początkowa pozycja X pierwszego bloku.
     */
    public static final float startX = (float) GameState.SCREEN_WIDTH / 2 - 245;

    /**
     * Początkowa pozycja Y pierwszego bloku.
     */
    public static final float startY = (float) GameState.SCREEN_HEIGHT / 2 + 200;

    /**
     * Konstruktor klasy Block.
     * Tworzy listę bloków w zależności od poziomu gry.
     *
     * @param level Poziom gry, który wpływa na układ bloków.
     */
    public Block(int level) {
        blocks = new Array<>();
        createBlocks(level);
    }

    /**
     * Rysuje bloki na ekranie.
     *
     * @param batch Obiekt SpriteBatch używany do rysowania.
     */
    public void drawBlocks(SpriteBatch batch) {
        for (Rectangle block : blocks) {
            if (block != null) {
                Assets.batch.draw(Assets.KwadratTexture, block.x, block.y, block.width, block.height);
            }
        }
    }

    /**
     * Tworzy bloki i umieszcza je w odpowiednich miejscach na ekranie.
     * Układ bloków zależy od poziomu gry.
     *
     * @param level Poziom gry, który wpływa na układ bloków.
     */
    private void createBlocks(int level) {
        float blockWidth = Block.blockWidth;
        float blockHeight = Block.blockHeight;

        Block.setNumberOfRows((level == 1) ? 3 : 4);
        Block.setNumberOfColumns(9);

        for (int i = 0; i < Block.getNumberOfRows(); i++) {
            for (int j = 0; j < Block.getNumberOfColumns(); j++) {
                float blockX = Block.startX + j * (blockWidth);
                float blockY = Block.startY - i * (blockHeight);

                Rectangle block = new Rectangle(blockX, blockY, blockWidth, blockHeight);
                blocks.add(block);
            }
        }
    }

    /**
     * Obsługuje kolizje piłki z blokami.
     * Po wykryciu kolizji usuwa blok i zmienia kierunek ruchu piłki.
     */
    public void handleCollisionWithBall() {
        Iterator<Rectangle> iterator = blocks.iterator();
        while (iterator.hasNext()) {
            Rectangle block = iterator.next();
            if (Ball.getBallY() < block.y + block.height &&
                    Ball.getBallY() + Ball.BallHeight > block.y &&
                    Ball.getBallX() < block.x + block.width &&
                    Ball.getBallX() + Ball.BallWidth > block.x) {
                // Kolizja z blokiem - dodaj punkty i usuń blok
                GameState.setScore(GameState.getScore() + 10);
                iterator.remove();

                // Odbij piłkę
                Ball.setBallDirectionY(Ball.getBallDirectionY() * -1);
                break;
            }
        }
    }

    /**
     * Zwraca liczbę wierszy bloków.
     *
     * @return Liczba wierszy bloków.
     */
    public static int getNumberOfRows() {
        return numberOfRows;
    }

    /**
     * Ustawia liczbę wierszy bloków.
     *
     * @param numberOfRows Nowa liczba wierszy bloków.
     */
    public static void setNumberOfRows(int numberOfRows) {
        Block.numberOfRows = numberOfRows;
    }

    /**
     * Zwraca liczbę kolumn bloków.
     *
     * @return Liczba kolumn bloków.
     */
    public static int getNumberOfColumns() {
        return numberOfColumns;
    }

    /**
     * Ustawia liczbę kolumn bloków.
     *
     * @param numberOfColumns Nowa liczba kolumn bloków.
     */
    public static void setNumberOfColumns(int numberOfColumns) {
        Block.numberOfColumns = numberOfColumns;
    }


    /**
     * Zwraca listę prostokątów reprezentujących bloki.
     *
     * @return Lista prostokątów reprezentujących bloki.
     */
    public Array<Rectangle> getBlocks() {
        return blocks;
    }
}
