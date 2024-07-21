package com.arkanoid.game;

import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input.Keys;
import com.badlogic.gdx.InputAdapter;
import com.badlogic.gdx.graphics.*;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.utils.Timer;

/**
 * Klasa główna gry Arkanoid. Zarządza głównymi elementami i logiką gry.
 */
public class Arkanoid extends ApplicationAdapter {

	/** Bloki do levela 1. */
	private Block blockLevel1;

	/** Bloki do levela 2. */
	private Block blockLevel2;

	/**
	 * Metoda wywoływana przy uruchomieniu gry.
	 * Inicjalizuje podstawowe elementy gry, takie jak bloki, muzyka, czcionki, kursor i obsługę wejścia.
	 */
	@Override
	public void create() {
		// Tworzenie bloków dla różnych poziomów gry
		blockLevel1 = new Block(1);
		blockLevel2 = new Block(2);

		//Muzyka
		Assets.load();
		Assets.music.setLooping(true);
		Assets.music.play();
		Assets.music.setVolume(0.2f);

		//Czcionka
		Assets.font.getData().setScale(Assets.initialSize);
		Assets.font2.getData().setScale(Assets.initialSize);

		//Kursor
		Gdx.graphics.setCursor(Gdx.graphics.newCursor(Assets.pm, 0, 0));

		Assets.batch = new SpriteBatch();

		//Stworzenie kamery
		OrthographicCamera camera = new OrthographicCamera(GameState.SCREEN_WIDTH, GameState.SCREEN_HEIGHT);
		camera.setToOrtho(false, GameState.SCREEN_WIDTH, GameState.SCREEN_HEIGHT);
		Assets.batch.setProjectionMatrix(camera.combined);

		/**
		 * Ustawienie obsługi wejścia (klawiatura i mysz).
		 * Ten fragment kodu odpowiada za konfigurację sposobu, w jaki gra reaguje na wejście użytkownika.
		 */
		Gdx.input.setInputProcessor(new InputAdapter() {

			@Override
			//Wcisniecie przycisku
			public boolean keyDown(int keycode) {

				//Wyjscie
				if (keycode == Keys.ESCAPE) {
					Gdx.app.exit();
					return true;
				}

				//Ruch w lewo
				if (keycode == Keys.A) {
					GameState.setWLewo(true);
					return true;
				}

				//Ruch w prawo
				if (keycode == Keys.D) {
					GameState.setWPrawo(true);
					return true;
				}

				// Obsluga spacji
				if (GameState.isRunning() && keycode == Keys.SPACE) {
					if (GameState.isSpaceVisible()) {
						GameState.setSpaceVisible(false);
						if (Ball.isStartingBall()) {
							Ball.setBallSpeed(400);
							Paddle.setPaddleSpeed(10f);
							Ball.setStartingBall(false);
						}
					} else {
						Ball.setBallSpeed(0);
						Paddle.setPaddleSpeed(0f);
						Ball.setStartingBall(true);
						GameState.setSpaceVisible(true);
					}
					return true;
				}
				//Wł/wył muzyki
				if (keycode == Keys.M) {
					OnOffMusic();
					return true;
				}

				return false;
			}

			@Override
			//Puszczenie przycisku
			public boolean keyUp(int keycode) {
				//Ruch w lewo
				if (keycode == Keys.A) {
					GameState.setWLewo(false);
					return true;
				}

				//Ruch w prawo
				if (keycode == Keys.D) {
					GameState.setWPrawo(false);
					return true;
				}

				return false;
			}

			/**
			 * Metoda wywoływana, gdy użytkownik naciśnie przycisk myszy.
			 * @param screenX Pozioma pozycja kursora w momencie naciśnięcia.
			 * @param screenY Pionowa pozycja kursora w momencie naciśnięcia.
			 * @param pointer Wskaźnik na urządzenie wejściowe, zazwyczaj 0 dla standardowej myszy.
			 * @param button Numer przycisku myszy, który został naciśnięty.
			 * @return true, aby wskazać, że zdarzenie zostało obsłużone.
			 */
			@Override
			public boolean touchDown(int screenX, int screenY, int pointer, int button) {

				// Konwersja współrzędnych ekranu na współrzędne gry
				float gameX = screenX / (float) Gdx.graphics.getWidth() * Gdx.graphics.getWidth();
				float gameY = Gdx.graphics.getHeight() - screenY / (float) Gdx.graphics.getHeight() * Gdx.graphics.getHeight();

				// Obsluga klikniecia myszka przycisku "New Game"
				if (GameState.isNewGameVisible() && gameX >= (float) GameState.SCREEN_WIDTH/2 - 95 && gameX <= (float) GameState.SCREEN_WIDTH/2 + 95 && gameY >= (float) GameState.SCREEN_HEIGHT/2 && gameY <= (float) GameState.SCREEN_HEIGHT/2 + 28) {
					GameState.setRunning(true);
					GameState.setSpaceVisible(true);
					GameState.setNewGameVisible(false);
					Ball.setBallSpeed(0);
					Paddle.setPaddleSpeed(0f);
					return true;
				}

				// Obsluga klikniecia myszka przycisku "Exit"
				if (!GameState.isRunning() && GameState.isNewGameVisible() && gameX >= (float) GameState.SCREEN_WIDTH/2 - 45 && gameX <= (float) GameState.SCREEN_WIDTH/2 + 45 && gameY >= (float) GameState.SCREEN_HEIGHT/2 - 45 && gameY <= (float) GameState.SCREEN_HEIGHT/2) {
					Gdx.app.exit();
					return true;
				}

				//Obsluga przycisku do wł/wył muzyki
				if (gameX >= 495 && gameX <=  540 && gameY >=  5 && gameY <= 55) {
					OnOffMusic();
					return true;
				}
				return false;
			}
		});
	}

	/**
	 * Metoda do włączania i wyłączania muzyki.
	 */
	public void OnOffMusic() {
		if (Assets.music.isPlaying()) {
			Assets.music.pause();
		}
		else {
			Assets.music.play();
		}
	}

	/**
	 * Metoda wyświetlająca ekran wygranej.
	 */
	public void EkranWygranej() {
		//Ustawienie parametrów
		Ball.setBallSpeed(0);
		Ball.setBallX((float) GameState.SCREEN_WIDTH / 2);
		Ball.setBallY((float) GameState.SCREEN_HEIGHT / 2);
		Paddle.setPaddleSpeed(0f);
		Paddle.setPaddleX((float) GameState.SCREEN_WIDTH/2 - 40);

		//Wypisanie Tekstu
		Assets.font.draw(Assets.batch, "YOU ARE A WINNER!!!", (float) GameState.SCREEN_WIDTH /2 - 210, (float) GameState.SCREEN_HEIGHT/2 - 20);
		Assets.font.draw(Assets.batch, "Your Score: " + GameState.getScore(), (float) GameState.SCREEN_WIDTH/2 - 145, (float) GameState.SCREEN_HEIGHT/2 - 63);

		// Ustaw timer na 10 sekund
		Timer.schedule(new Timer.Task() {
			@Override
			public void run() {
				Gdx.app.exit();
			}
		}, 10);
	}

	/**
	 * Metoda wyświetlająca ekran przegranej.
	 */
	public void EkranPrzegranej() {
		//Ustawienie parametrów
		Ball.setBallSpeed(0);
		Paddle.setPaddleSpeed(0);

		//Wypisanie Tekstu
		Assets.font.draw(Assets.batch, "You Lose!", (float) GameState.SCREEN_WIDTH / 2 - 95, (float) GameState.SCREEN_HEIGHT / 2 - 20);
		Assets.font.draw(Assets.batch, "Your Score: " + GameState.getScore(), (float) GameState.SCREEN_WIDTH / 2 - 145, (float) GameState.SCREEN_HEIGHT / 2 - 63);

			// Ustaw timer na 10 sekund
			Timer.schedule(new Timer.Task() {
				@Override
				public void run() {
					Gdx.app.exit();
				}
			}, 10);
	}

	/**
	 * Metoda zarządzająca rozgrywką na danym poziomie.
	 * @param level Poziom gry.
	 */
	public void Rozgrywka(int level) {
		//Obsluga ruchu paletki
		if (GameState.isWLewo()) {
			Paddle.moveLeft();
		}
		if (GameState.isWPrawo()) {
			Paddle.moveRight();
		}

		if (GameState.isLoser()) {
			GameState.setSpaceVisible(false);
			EkranPrzegranej();
		}

		if (GameState.isWinner() && level == 2) {
			GameState.setSpaceVisible(false);
			EkranWygranej();
		}

		if (GameState.isSpaceVisible()) {
			Assets.font2.draw(Assets.batch, "Press 'SPACE' to start",(float) GameState.SCREEN_WIDTH/2 - 220,(float) GameState.SCREEN_WIDTH/2);
		}

		if(level == 1) {
			blockLevel1.handleCollisionWithBall();

		} else if (level == 2) {
			blockLevel2.handleCollisionWithBall();
		}

		Assets.font.draw(Assets.batch, "Health:",25, 30);
		Assets.font.draw(Assets.batch, "Score:" + GameState.getScore(), 25, 590);

		if(level == 1) {
			Assets.font.draw(Assets.batch, "Level:1", 380, 590);
		}
		else if (level == 2) {
			Assets.font.draw(Assets.batch, "Level:2", 380, 590);
		}

		//Zycia
		Health.drawLives(Assets.batch, Health.getHealthCounter());

		//Poruszanie pilki i kolizje ze scianami
		Ball.move();
		Ball.checkWallCollision();
		Ball.checkCeilingCollision();
		Ball.checkFloorCollision();

		// Sprawdź kolizję z paletką
		Paddle.checkCollisionWithBall();

		//rysowanie blokow
		if(level == 1) {
			blockLevel1.drawBlocks(Assets.batch);

		}
		else if (level == 2) {
			blockLevel2.drawBlocks(Assets.batch);
		}

		if(level == 1) {
			if(GameState.getScore() >= 270) {
			Ball.setBallSpeed(0);
			Paddle.setPaddleSpeed(0);
			Paddle.setPaddleX((float) GameState.SCREEN_WIDTH/2 - 40);
			Ball.setBallX((float) GameState.SCREEN_WIDTH/2);
			Ball.setBallY((float) GameState.SCREEN_HEIGHT/2);
			Ball.setStartingBall(true);
			GameState.setLevelComplete(true);
			GameState.setSpaceVisible(true);
			Ball.setBallDirectionX(0);
			return;
			}
		}
		else if (level == 2) {
			if(GameState.getScore() >= 630)
				GameState.setWinner(true);
		}

		Ball.draw(Assets.batch);
	}

	/**
	 * Główna metoda rysująca elementy gry.
	 * Wywoływana jest w każdej klatce gry.
	 */
	@Override
	public void render() {
		Assets.batch.begin();

		Texture currentBg = GameState.isRunning() ? Assets.bg2 : Assets.bg;
		Texture currentMusic = Assets.music.isPlaying() ? Assets.MusicOn : Assets.MusicOff;
		Assets.batch.draw(currentBg, 0, 0);
		Assets.batch.draw(currentMusic, 510, 10);

		// Rysowanie tekstu "New Game" i "Exit"
		if (GameState.isNewGameVisible()) {
			Assets.font.draw(Assets.batch, "New Game", (float) GameState.SCREEN_WIDTH /2 - 85, (float) GameState.SCREEN_HEIGHT/2 + 28);
			Assets.font.draw(Assets.batch, "Exit", (float) GameState.SCREEN_WIDTH/2 - 40, (float) GameState.SCREEN_HEIGHT/2 - 15);
		}

		//Rozpoczecie rozgrywki
		if (GameState.isRunning()) {
			if(!GameState.isLevelComplete()){
				Rozgrywka(1);
			}
			if(GameState.isLevelComplete()) {
				Rozgrywka(2);
			}
			Paddle.draw(Assets.batch);
		}
		Assets.batch.end();
	}

	/**
	 * Metoda wywoływana przy zamykaniu gry.
	 * Odpowiada za zwolnienie zasobów.
	 */
	@Override
	public void dispose() {
		new Assets().dispose();
	}
}