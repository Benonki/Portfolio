/**
 * Klasa testująca funkcje związane z licznikiem zdrowia (Health) w grze Arkanoid.
 * Testuje pobieranie i ustawianie wartości licznika zdrowia.
 */
package com.arkanoid.game;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class HealthTest {

    /**
     * Testuje poprawność pobierania wartości licznika zdrowia.
     */
    @Test
    public void testGetHealthCounter() {
        // Ustawienie początkowej wartości licznika zdrowia
        int initialHealthCounter = 3;
        Health.setHealthCounter(initialHealthCounter);

        // Pobranie wartości licznika zdrowia i porównanie z początkową wartością
        int result = Health.getHealthCounter();
        assertEquals(initialHealthCounter, result);
    }

    /**
     * Testuje poprawność ustawiania wartości licznika zdrowia.
     */
    @Test
    public void testSetHealthCounter() {
        // Ustawienie początkowej wartości licznika zdrowia
        int initialHealthCounter = 3;
        Health.setHealthCounter(initialHealthCounter);

        // Pobranie zaktualizowanej wartości licznika zdrowia i porównanie z początkową wartością
        int updatedHealthCounter = Health.getHealthCounter();
        assertEquals(initialHealthCounter, updatedHealthCounter);
    }
}
