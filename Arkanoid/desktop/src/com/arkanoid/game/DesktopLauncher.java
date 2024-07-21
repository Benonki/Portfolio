package com.arkanoid.game;

import com.badlogic.gdx.backends.lwjgl3.Lwjgl3Application;
import com.badlogic.gdx.backends.lwjgl3.Lwjgl3ApplicationConfiguration;

/**
 * Klasa uruchamiająca grę Arkanoid na pulpicie.
 */
public class DesktopLauncher {

	/**
	 * Główny punkt wejścia aplikacji.
	 *
	 * @param arg Argumenty przekazane do aplikacji (nieużywane w tej aplikacji).
	 */
	public static void main(String[] arg) {
		// Konfiguracja aplikacji dla biblioteki LWJGL3
		Lwjgl3ApplicationConfiguration config = new Lwjgl3ApplicationConfiguration();

		// Ustawienie maksymalnej liczby klatek na sekundę na 60
		config.setForegroundFPS(60);

		// Ustawienie tytułu okna gry
		config.setTitle("Arkanoid");

		// Ustawienie trybu okna zgodnie z rozmiarem określonym w GameState
		config.setWindowedMode(GameState.SCREEN_WIDTH, GameState.SCREEN_HEIGHT);

		// Ustawienie ikony okna
		config.setWindowIcon("images/icon32.png");

		// Zablokowanie możliwości zmiany rozmiaru okna
		config.setResizable(false);

		// Tworzenie i uruchamianie aplikacji z użyciem konfiguracji i głównej klasy gry
		new Lwjgl3Application(new Arkanoid(), config);
	}
}