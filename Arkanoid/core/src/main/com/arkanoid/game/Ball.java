package com.arkanoid.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

/**
 * Klasa reprezentująca piłkę w grze Arkanoid.
 */
public class Ball {

    /** Zmienna określająca, czy piłka jest w stanie początkowym. */
    private static boolean startingBall = true;

    /** Poziomy kierunek ruchu piłki. */
    private static float BallDirectionX = 0;

    /** Pionowy kierunek ruchu piłki. */
    private static float BallDirectionY = -1;

    /** Położenie X piłki na ekranie. */
    private static float BallX = (float) GameState.SCREEN_WIDTH/2;

    /** Położenie Y piłki na ekranie. */
    private static float BallY = (float) GameState.SCREEN_HEIGHT/2;

    /** Szerokość piłki. */
    public static final float BallWidth = 22;

    /** Wysokość piłki. */
    public static final float BallHeight = 24;

    /** Prędkość piłki. */
    public static float BallSpeed = 400;

    /**
     * Sprawdza, czy piłka jest w stanie początkowym.
     * @return true, jeśli piłka jest w stanie początkowym.
     */
    public static boolean isStartingBall() {
        return startingBall;
    }

    /**
     * Ustawia stan początkowy piłki.
     * @param startingBall stan początkowy piłki.
     */
    public static void setStartingBall(boolean startingBall) {
        Ball.startingBall = startingBall;
    }

    /**
     * Przemieszcza piłkę zgodnie z jej aktualnym kierunkiem i prędkością.
     */
    public static void move() {
        float deltaTime = Gdx.graphics.getDeltaTime();

        Ball.setBallX(Ball.getBallX() + Ball.getBallDirectionX() * Ball.getBallSpeed() * deltaTime);
        Ball.setBallY(Ball.getBallY() + Ball.getBallDirectionY() * Ball.getBallSpeed() * deltaTime);
    }

    /**
     * Sprawdza i obsługuje kolizję piłki ze ścianami.
     */
    public static void checkWallCollision() {
        if (Ball.getBallX() - 20 < 0 || Ball.getBallX() + Ball.BallWidth + 20 > Gdx.graphics.getWidth()) {
            Ball.setBallDirectionX(Ball.getBallDirectionX() * -1);
        }
    }

    /**
     * Sprawdza i obsługuje kolizję piłki z sufitem.
     */
    public static void checkCeilingCollision() {
        if (Ball.getBallY() + Ball.BallHeight + 20 > Gdx.graphics.getHeight()) {
            Ball.setBallDirectionY(Ball.getBallDirectionY() * -1);
        }
    }

    /**
     * Sprawdza i obsługuje kolizję piłki z podłogą.
     */
    public static void checkFloorCollision() {
        if (Ball.getBallY() - 20 < 0) {
            handleFloorCollision();
        }
    }

    /**
     * Obsługuje sytuację, gdy piłka dotyka podłogi.
     */
    public static void handleFloorCollision() {
        GameState.setSpaceVisible(true);
        Health.setHealthCounter(Health.getHealthCounter() - 1);

        if (Health.getHealthCounter() == 0) {
            GameState.setLoser(true);
        } else {
            resetBallPosition();
        }
    }

    /**
     * Resetuje pozycję i prędkość piłki do stanu początkowego.
     */
    public static void resetBallPosition() {
        Ball.setBallX((float) GameState.SCREEN_WIDTH / 2);
        Ball.setBallY((float) GameState.SCREEN_HEIGHT / 2);
        Ball.setBallSpeed(0);
        Ball.setBallDirectionX(0);
        Ball.setBallDirectionY(-1);
        Paddle.setPaddleSpeed(0);
        Paddle.setPaddleX((float) GameState.SCREEN_WIDTH / 2 - 40);
        setStartingBall(true);
    }

    /**
     * Rysuje piłkę na ekranie.
     * @param batch SpriteBatch służący do rysowania.
     */
    public static void draw(SpriteBatch batch){
        Assets.batch.draw(Assets.pilkaTexture, Ball.getBallX(), Ball.getBallY(), Ball.BallWidth, Ball.BallHeight);
    }

    /**
     * Zwraca aktualną pozycję X piłki.
     * @return Pozycja X piłki.
     */
    public static float getBallX() {
        return BallX;
    }

    /**
     * Ustawia pozycję X piłki.
     * @param ballX Nowa pozycja X piłki.
     */
    public static void setBallX(float ballX) {
        BallX = ballX;
    }

    /**
     * Zwraca aktualną pozycję Y piłki.
     * @return Pozycja Y piłki.
     */
    public static float getBallY() {
        return BallY;
    }

    /**
     * Ustawia pozycję Y piłki.
     * @param ballY Nowa pozycja Y piłki.
     */
    public static void setBallY(float ballY) {
        BallY = ballY;
    }

    /**
     * Zwraca aktualną prędkość piłki.
     * @return Prędkość piłki.
     */
    public static float getBallSpeed() {
        return BallSpeed;
    }

    /**
     * Ustawia prędkość piłki.
     * @param speed Nowa prędkość piłki.
     */
    public static void setBallSpeed(float speed) {
        BallSpeed = speed;
    }

    /**
     * Zwraca kierunek poziomy (X) piłki.
     * @return Kierunek poziomy piłki.
     */
    public static float getBallDirectionX() {
        return BallDirectionX;
    }

    /**
     * Ustawia kierunek poziomy (X) piłki.
     * @param ballDirectionX Nowy kierunek poziomy piłki.
     */
    public static void setBallDirectionX(float ballDirectionX) {
        BallDirectionX = ballDirectionX;
    }

    /**
     * Zwraca kierunek pionowy (Y) piłki.
     * @return Kierunek pionowy piłki.
     */
    public static float getBallDirectionY() {
        return BallDirectionY;
    }

    /**
     * Ustawia kierunek pionowy (Y) piłki.
     * @param ballDirectionY Nowy kierunek pionowy piłki.
     */
    public static void setBallDirectionY(float ballDirectionY) {
        BallDirectionY = ballDirectionY;
    }

}
