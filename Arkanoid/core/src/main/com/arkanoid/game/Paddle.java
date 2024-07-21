package com.arkanoid.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.utils.Timer;
/**
 * Klasa Paddle zarządza paletką w grze Arkanoid.
 */
public class Paddle{

    /** Początkowa pozycja Y paletki. */
    private static final float PaddleY = 45;

    /** Początkowa pozycja X paletki. */
    private static float PaddleX = (float) GameState.SCREEN_WIDTH / 2 - 40;

    /** Prędkość paletki. */
    private static float PaddleSpeed = 10f;

    /** Flag, która wskazuje, czy paletka została uderzona. */
    private static boolean paddleHit = false;

    /** Szerokość paletki. */
    public static final float paddleWidth = 100;

    /** Wysokość paletki. */
    public static final float paddleHeight = 30;

    /**
     * Rysuje paletkę na ekranie.
     *
     * @param batch Obiekt SpriteBatch do rysowania.
     */
    public static void draw(SpriteBatch batch) {
        batch.draw(Assets.paletkaTexture, PaddleX, PaddleY, paddleWidth, paddleHeight);
    }

    /**
     * Sprawdza kolizję paletki z piłką.
     */
    public static void checkCollisionWithBall() {
        if (Ball.getBallY() < PaddleY + paddleHeight &&
                Ball.getBallY() + Ball.BallHeight > PaddleY &&
                Ball.getBallX() < PaddleX + paddleWidth &&
                Ball.getBallX() + Ball.BallWidth > PaddleX) {

            // Odbij piłkę
            float paddleCenterX = PaddleX + paddleWidth / 2;
            float distanceFromCenter = Ball.getBallX() + Ball.BallWidth / 2 - paddleCenterX;
            float normalizedDistance = distanceFromCenter / (paddleWidth / 2);

            Ball.setBallDirectionY(1);

            float impactStrength = 0.5f;
            Ball.setBallDirectionX(normalizedDistance * impactStrength);

            if (!Paddle.isPaddleHit()) {
                Paddle.setPaddleHit(true);

                Texture temp = Assets.paletkaTexture;
                Assets.paletkaTexture = Assets.paletkaTexture2;
                Assets.paletkaTexture2 = temp;

                Timer.schedule(new Timer.Task() {
                    @Override
                    public void run() {
                        Texture temp = Assets.paletkaTexture;
                        Assets.paletkaTexture = Assets.paletkaTexture2;
                        Assets.paletkaTexture2 = temp;

                        Paddle.setPaddleHit(false);
                    }
                }, 0.2f);
            }
        }
    }

    /**
     * Przesuwa paletkę w lewo.
     */
    public static void moveLeft() {
        if (PaddleX - PaddleSpeed > 20) {
            PaddleX -= PaddleSpeed;
        } else {
            PaddleX = 20;
        }
    }

    /**
     * Przesuwa paletkę w prawo.
     */
    public static void moveRight() {
        // Assuming PaddleX and PaddleSpeed are global variables
        // Adjust the condition based on your game's requirements
        if (PaddleX + PaddleSpeed < 460) {
            PaddleX += PaddleSpeed;
        } else {
            PaddleX = 460;
        }
    }

    /**
     * Zwraca informację, czy paletka została uderzona.
     *
     * @return true, jeśli paletka została uderzona.
     */
    public static boolean isPaddleHit() {
        return paddleHit;
    }

    /**
     * Ustawia stan uderzenia paletki.
     *
     * @param paddleHit Stan uderzenia paletki.
     */
    public static void setPaddleHit(boolean paddleHit) {
        Paddle.paddleHit = paddleHit;
    }

    /**
     * Ustawia prędkość paletki.
     *
     * @param speed Prędkość paletki.
     */
    public static void setPaddleSpeed(float speed) {
        PaddleSpeed = speed;
    }

    /**
     * Zwraca wspolrzedna Y paletki.
     */
    public static float getPaddleY() {
        return PaddleY;
    }

    /**
     * Zwraca wspolrzedna X paletki.
     */
    public static float getPaddleX() {
        return PaddleX;
    }

    /**
     * Zwraca predkosc paletki.
     */
    public static float getPaddleSpeed(){
        return PaddleSpeed;
    }

    /**
     * Ustawia pozycję X paletki.
     *
     * @param PaddleX Pozycja X paletki.
     */
    public static void setPaddleX(float PaddleX) {
        Paddle.PaddleX = PaddleX;
    }
}