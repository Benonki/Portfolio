package com.arkanoid.game;

// Importy z frameworka LibGDX
import com.badlogic.gdx.Gdx; // Zapewnia klasy do zarządzania cyklem życia gry oraz wejściem/wyjściem systemowym.
import com.badlogic.gdx.audio.Music; // Używane do ładowania i odtwarzania plików audio.
import com.badlogic.gdx.graphics.Pixmap; // Do manipulowania obrazami w pamięci.
import com.badlogic.gdx.graphics.Texture; // Do obsługi tekstur (obrazów) używanych w grze.
import com.badlogic.gdx.graphics.g2d.BitmapFont; // Obsługuje renderowanie czcionek w grze.
import com.badlogic.gdx.graphics.g2d.SpriteBatch; // Umożliwia efektywne renderowanie sprite'ów w grze.
import com.badlogic.gdx.utils.Disposable; // Interfejs do czyszczenia zasobów.


/**
 * Klasa Assets zawiera zasoby używane w grze Arkanoid, takie jak tekstury, muzyka i czcionki.
 */
public class Assets implements Disposable{

    /** Tekstura tła Menu. */
    public static Texture bg;

    /** Tekstura tła Gry. */
    public static Texture bg2;

    /** Tekstura Paletki. */
    public static Texture paletkaTexture;

    /** Tekstura Paletki (gdy jest odbijana od piłki). */
    public static Texture paletkaTexture2;

    /** Tekstura Piłki. */
    public static Texture pilkaTexture;

    /** Tekstura bloków. */
    public static Texture KwadratTexture;

    /** Tekstura Muzyki włączonej. */
    public static Texture MusicOn;

    /** Tekstura Muzyki wyłączonej. */
    public static Texture MusicOff;

    /** Muzyka w tle. */
    public static Music music;

    /** Umożliwia nam ustawianie rzeczy na scenie. */
    public static SpriteBatch batch;

    /** Pierwsza czcionka. */
    public static BitmapFont font;

    /** Druga czcionka. */
    public static BitmapFont font2;

    /** Tekstura kursora. */
    public static Pixmap pm;

    /** Tekstura Serc (życia). */
    public static Texture heartTexture;

    /** Rozmiar czcionki (startowa). */
    public static float initialSize = 1.0f;

    /**
     * Ładuje zasoby gry, w tym tekstury, czcionki i muzykę.
     */
    public static void load() {
        try {
        //Tekstury
        bg = new Texture("images/background.png");
        bg2 = new Texture("images/background2.png");
        paletkaTexture = new Texture("images/paddle1.png");
        paletkaTexture2 = new Texture("images/paddle2.png");
        pilkaTexture = new Texture("images/ball.png");
        KwadratTexture = new Texture("images/rectangle.png");
        MusicOn = new Texture("images/MusicOn.png");
        MusicOff = new Texture("images/MusicOff.png");
        heartTexture = new Texture("images/health.png");
        pm = new Pixmap(Gdx.files.internal("images/cursor.png"));

        //Czcionka
        font = new BitmapFont(Gdx.files.internal("font.fnt"));
        font2 = new BitmapFont(Gdx.files.internal("font2.fnt"));

        //Muzyka
        music = Gdx.audio.newMusic(Gdx.files.internal("song.mp3"));
        } catch (Exception e) {
            // Obsługa wyjątku
            Gdx.app.error("Assets", "Błąd podczas ładowania zasobów: " + e.getMessage());
            // Zamykanie aplikacji
            Gdx.app.exit();
        }
    }

    /**
     * Zwalnia zasoby używane przez grę.
     */
    @Override
    public void dispose() {
        bg.dispose();
        bg2.dispose();
        paletkaTexture.dispose();
        pilkaTexture.dispose();
        KwadratTexture.dispose();
        MusicOn.dispose();
        MusicOff.dispose();
        music.dispose();
        pm.dispose();
        batch.dispose();
        font.dispose();
        heartTexture.dispose();
    }
}