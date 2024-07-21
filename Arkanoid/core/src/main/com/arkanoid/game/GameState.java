package com.arkanoid.game;

/**
 * Klasa GameState reprezentuje i zarządza stanem gry Arkanoid.
 * Przechowuje informacje o bieżącym stanie gry oraz udostępnia metody do jego zmiany.
 */
public class GameState {

    /** Określa, czy gra jest aktualnie uruchomiona. */
    private static boolean running = false;

    /** Określa, czy przycisk rozpoczęcia nowej gry jest widoczny. */
    private static boolean newGameVisible = true;

    /** Określa, czy paletka porusza się w lewo. */
    private static boolean wLewo = false;

    /** Określa, czy paletka porusza się w prawo. */
    private static boolean wPrawo = false;

    /** Określa, czy przycisk spacji jest widoczny (używany do startu gry). */
    private static boolean spaceVisible = true;

    /** Określa, czy bieżący poziom gry został ukończony. */
    private static boolean levelComplete = false;

    /** Określa, czy gracz wygrał grę. */
    private static boolean winner = false;

    /** Określa, czy gracz przegrał grę. */
    private static boolean loser = false;

    /** Przechowuje bieżący wynik gracza. */
    private static int score = 0;

    /** Stała określająca szerokość ekranu gry. */
    public static final int SCREEN_WIDTH = 573;

    /** Stała określająca wysokość ekranu gry. */
    public static final int SCREEN_HEIGHT = 614;

    /**
     * Sprawdza, czy gra jest aktualnie uruchomiona.
     *
     * @return true, jeśli gra jest uruchomiona; false w przeciwnym razie.
     */
    public static boolean isRunning() {
        return running;
    }

    /** Ustawia stan gry na uruchomioną lub zatrzymaną. */
    public static void setRunning(boolean running) {
        GameState.running = running;
    }

    /**
     * Sprawdza, czy przycisk rozpoczęcia nowej gry jest widoczny.
     *
     * @return true, jeśli przycisk jest widoczny; false w przeciwnym razie.
     */
    public static boolean isNewGameVisible() {
        return newGameVisible;
    }

    /** Ustawia widoczność przycisku nowej gry. */
    public static void setNewGameVisible(boolean newGameVisible) {
        GameState.newGameVisible = newGameVisible;
    }

    /**
     * Sprawdza, czy paletka jest sterowana do poruszania się w lewo.
     *
     * @return true, jeśli paletka porusza się w lewo; false w przeciwnym razie.
     */
    public static boolean isWLewo() {
        return wLewo;
    }

    /** Ustawia ruch paletki w lewo. */
    public static void setWLewo(boolean wLewo) {
        GameState.wLewo = wLewo;
    }

    /**
     * Sprawdza, czy paletka jest sterowana do poruszania się w prawo.
     *
     * @return true, jeśli paletka porusza się w prawo; false w przeciwnym razie.
     */
    public static boolean isWPrawo() {
        return wPrawo;
    }

    /** Ustawia ruch paletki w prawo. */
    public static void setWPrawo(boolean wPrawo) {
        GameState.wPrawo = wPrawo;
    }

    /**
     * Sprawdza, czy przycisk spacji jest widoczny (używany do startu piłki).
     *
     * @return true, jeśli przycisk spacji jest widoczny; false w przeciwnym razie.
     */
    public static boolean isSpaceVisible() {
        return spaceVisible;
    }

    /** Ustawia widoczność przycisku spacji. */
    public static void setSpaceVisible(boolean spaceVisible) {
        GameState.spaceVisible = spaceVisible;
    }

    /**
     * Sprawdza, czy bieżący poziom gry został ukończony.
     *
     * @return true, jeśli poziom został ukończony; false w przeciwnym razie.
     */
    public static boolean isLevelComplete() {
        return levelComplete;
    }

    /** Ustawia stan ukończenia bieżącego poziomu. */
    public static void setLevelComplete(boolean levelComplete) {
        GameState.levelComplete = levelComplete;
    }

    /**
     * Sprawdza, czy gracz wygrał grę.
     *
     * @return true, jeśli gracz wygrał; false w przeciwnym razie.
     */
    public static boolean isWinner() {
        return winner;
    }

    /** Ustawia stan wygranej gracza. */
    public static void setWinner(boolean winner) {
        GameState.winner = winner;
    }

    /**
     * Sprawdza, czy gracz przegrał grę.
     *
     * @return true, jeśli gracz przegrał; false w przeciwnym razie.
     */
    public static boolean isLoser() {
        return loser;
    }

    /** Ustawia stan przegranej gracza. */
    public static void setLoser(boolean loser) {
        GameState.loser = loser;
    }

    /**
     * Zwraca aktualny wynik gracza.
     *
     * @return Wynik gracza jako liczba całkowita.
     */
    public static int getScore() {
        return score;
    }

    /** Ustawia wynik gracza. */
    public static void setScore(int score) {
        GameState.score = score;
    }
}
