package com.arkanoid.game;

import com.badlogic.gdx.graphics.g2d.SpriteBatch;

/**
 * Klasa Health zarządza i wyświetla życia gracza w grze.
 */
public class Health {

    /** Pozycja x serca na ekranie. */
    private static float heartX;

    /** Pozycja y serca na ekranie. */
    private static float heartY;

    /** Licznik zdrowia (liczba żyć gracza). */
    private static int healthCounter = 3;

    /**
     * Rysuje określoną liczbę serc (żyć) na ekranie.
     *
     * @param batch Obiekt SpriteBatch służący do rysowania na ekranie.
     * @param numberOfLives Liczba serc (żyć) do narysowania.
     */
    public static void drawLives(SpriteBatch batch, int numberOfLives) {
        for (int i = 0; i < numberOfLives; i++) {
            heartX = (190 + i * 40);
            heartY = -5;
            batch.draw(Assets.heartTexture, heartX, heartY, 40, 40);
        }
    }

    /**
     * Zwraca aktualną liczbę żyć gracza.
     *
     * @return Aktualna liczba żyć.
     */
    public static int getHealthCounter() { return healthCounter; }

    /**
     * Ustawia liczbę żyć gracza.
     *
     * @param healthCounter Nowa liczba żyć.
     */
    public static void setHealthCounter(int healthCounter) {
        Health.healthCounter = healthCounter;
    }
}
