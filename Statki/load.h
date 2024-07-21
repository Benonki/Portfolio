#pragma once //aby plik zosta³ skompilowany tylko raz

#include "Gra w Statki.h" //do³¹czenie reszty potrzebnych rzeczy

sf::SoundBuffer placeShipSoundBuffer; //bufor, bêdzie przechowywa³ dŸwiêk po³o¿enia statku
sf::Sound placeShipSound; //dŸwiêk polozenia statku
sf::SoundBuffer hitSoundBuffer; //bufor, bêdzie przechowywa³ dŸwiêk trafienia statku
sf::Sound hitSound; //dŸwiêk trafienia statku
sf::SoundBuffer missSoundBuffer; //bufor, bêdzie przechowywa³ dŸwiêk chybienia
sf::Sound missSound; //dŸwiêk chybienia
sf::SoundBuffer gameOverSoundBuffer; //bufor, bêdzie przechowywa³ dŸwiêk koñca gry
sf::Sound gameOverSound; //dŸwiêk koñca gry
sf::Music backgroundMusic; //muzyka w tle
sf::Texture emptyTexture; //tekstura pustego pola
sf::Texture shipTexture; //tekstura pola ze statkiem
sf::Texture hitTexture; //tekstura pola, gdzie trafiono statek
sf::Texture missTexture; // tektura pola, gdzie nie trafiono w statek
sf::Texture highlightedTexture; //tekstura podœwietlonego pola
sf::Texture bombTexture; //tektura pola z bomb¹
sf::Texture backgroundTexture; //tekstura t³a menu
sf::Texture backgroundTexture1; //tektura t³a podczas rozgrywki
sf::Texture cursorTexture; //tekstura kursora
sf::Texture start, start1, tryb, tryb1, wyjdz, wyjdz1, music, music1, music2, music2b, graczvsgracz, graczvsgracz1, graczvsgracz2, graczvsai, graczvsai1, graczvsai2, bomby, bomby1, bomby2, bezbomb, bezbomb1, bezbomb2, kolejgraczanr1, kolejgraczanr2, komputermysli, planszagracza, planszagracza1, planszagracza2, planszakomputera, wygenGracz, wygenGracznr1, wygenGracznr2, twojakolej, wyjscietlo, wyjscietlo1, music4, music4b, music5, music5b, zakonczenie1, zakonczenie2, zakonczenie3, zakonczenie4, wersja; //pozostale tekstury

class Load { //klasa odpowiad¹jaca za za³adowanie wszystkich danych (grafika i audio)
public:
    static bool loadGraphics() //metoda ³aduj¹ca grafikê ca³ej gry
    {
        try {
            if (!emptyTexture.loadFromFile("grafika/empty.png")) //za³adowanie tektury pustego pola z pliku (poni¿ej odpowiednio dla reszty tekstur)
                throw std::runtime_error("Nie udalo sie wczytac empty.png"); //obs³uga wyj¹tku (poni¿ej odpowiednio dla reszty wyj¹tków)
            if (!shipTexture.loadFromFile("grafika/ship.png"))
                throw std::runtime_error("Nie udalo sie wczytac ship.png");
            if (!hitTexture.loadFromFile("grafika/hit.png"))
                throw std::runtime_error("Nie udalo sie wczytac hit.png");
            if (!missTexture.loadFromFile("grafika/miss.png"))
                throw std::runtime_error("Nie udalo sie wczytac miss.png");
            if (!highlightedTexture.loadFromFile("grafika/highlighted.png"))
                throw std::runtime_error("Nie udalo sie wczytac highlighted.png");
            if (!bombTexture.loadFromFile("grafika/bomba.png"))
                throw std::runtime_error("Nie udalo sie wczytac bomba.png");
            if (!backgroundTexture.loadFromFile("grafika/tlo.png"))
                throw std::runtime_error("Nie udalo sie wczytac tlo.png");
            if (!backgroundTexture1.loadFromFile("grafika/tlo1.png"))
                throw std::runtime_error("Nie udalo sie wczytac tlo1.png");
            if (!cursorTexture.loadFromFile("grafika/kursorStatki48_1.png"))
                throw std::runtime_error("Nie udalo sie wczytac kursorStatki48_1.png");
            if (!start.loadFromFile("grafika/Start.png"))
                throw std::runtime_error("Nie udalo sie wczytac Start.png");
            if (!start1.loadFromFile("grafika/Start2.png"))
                throw std::runtime_error("Nie udalo sie wczytac Start2.png");
            if (!tryb.loadFromFile("grafika/Tryb.png"))
                throw std::runtime_error("Nie udalo sie wczytac Tryb.png");
            if (!tryb1.loadFromFile("grafika/Tryb2.png"))
                throw std::runtime_error("Nie udalo sie wczytac Tryb2.png");
            if (!wyjdz.loadFromFile("grafika/Wyjdz.png"))
                throw std::runtime_error("Nie udalo sie wczytac Wyjdz.png");
            if (!wyjdz1.loadFromFile("grafika/Wyjdz2.png"))
                throw std::runtime_error("Nie udalo sie wczytac Wyjdz2.png");
            if (!music.loadFromFile("grafika/Music.png"))
                throw std::runtime_error("Nie udalo sie wczytac Music.png");
            if (!music1.loadFromFile("grafika/Music2.png"))
                throw std::runtime_error("Nie udalo sie wczytac Music2.png");
            if (!music2.loadFromFile("grafika/Music3.png"))
                throw std::runtime_error("Nie udalo sie wczytac Music3.png");
            if (!music2b.loadFromFile("grafika/Music3b.png"))
                throw std::runtime_error("Nie udalo sie wczytac Music3b.png");
            if (!graczvsgracz.loadFromFile("grafika/GraczVsGracz.png"))
                throw std::runtime_error("Nie udalo sie wczytac GraczVsGracz.png");
            if (!graczvsgracz1.loadFromFile("grafika/GraczVsGracz2.png"))
                throw std::runtime_error("Nie udalo sie wczytac GraczVsGracz2.png");
            if (!graczvsgracz2.loadFromFile("grafika/GraczVsGracz3.png"))
                throw std::runtime_error("Nie udalo sie wczytac GraczVsGracz3.png");
            if (!graczvsai.loadFromFile("grafika/GraczVsAi.png"))
                throw std::runtime_error("Nie udalo sie wczytac GraczVsAi.png");
            if (!graczvsai1.loadFromFile("grafika/GraczVsAi2.png"))
                throw std::runtime_error("Nie udalo sie wczytac GraczVsAi2.png");
            if (!graczvsai2.loadFromFile("grafika/GraczVsAi3.png"))
                throw std::runtime_error("Nie udalo sie wczytac GraczVsAi3.png");
            if (!bomby.loadFromFile("grafika/Bomby.png"))
                throw std::runtime_error("Nie udalo sie wczytac Bomby.png");
            if (!bomby1.loadFromFile("grafika/Bomby2.png"))
                throw std::runtime_error("Nie udalo sie wczytac Bomby2.png");
            if (!bomby2.loadFromFile("grafika/Bomby3.png"))
                throw std::runtime_error("Nie udalo sie wczytac Bomby3.png");
            if (!bezbomb.loadFromFile("grafika/BezBomb.png"))
                throw std::runtime_error("Nie udalo sie wczytac BezBomb.png");
            if (!bezbomb1.loadFromFile("grafika/BezBomb2.png"))
                throw std::runtime_error("Nie udalo sie wczytac BezBomb2.png");
            if (!bezbomb2.loadFromFile("grafika/BezBomb3.png"))
                throw std::runtime_error("Nie udalo sie wczytac BezBomb3.png");
            if (!kolejgraczanr1.loadFromFile("grafika/KolejGraczaNr1.png"))
                throw std::runtime_error("Nie udalo sie wczytac KolejGraczaNr1.png");
            if (!kolejgraczanr2.loadFromFile("grafika/KolejGraczaNr2.png"))
                throw std::runtime_error("Nie udalo sie wczytac KolejGraczaNr2.png");
            if (!komputermysli.loadFromFile("grafika/KomputerMysli.png"))
                throw std::runtime_error("Nie udalo sie wczytac KomputerMysli.png");
            if (!planszagracza.loadFromFile("grafika/PlanszaGracza.png"))
                throw std::runtime_error("Nie udalo sie wczytac PlanszaGracza.png");
            if (!planszagracza1.loadFromFile("grafika/PlanszaGraczaNr1.png"))
                throw std::runtime_error("Nie udalo sie wczytac PlanszaGraczaNr1.png");
            if (!planszagracza2.loadFromFile("grafika/PlanszaGraczaNr2.png"))
                throw std::runtime_error("Nie udalo sie wczytac PlanszaGraczaNr2.png");
            if (!planszakomputera.loadFromFile("grafika/PlanszaKomputera.png"))
                throw std::runtime_error("Nie udalo sie wczytac PlanszaKomputera.png");
            if (!wygenGracz.loadFromFile("grafika/GraczRozstawiaStatki.png"))
                throw std::runtime_error("Nie udalo sie wczytac GraczRozstawiaStatki.png");
            if (!wygenGracznr1.loadFromFile("grafika/GraczNr1RozstawiaStatki.png"))
                throw std::runtime_error("Nie udalo sie wczytac GraczNr1RozstawiaStatki.png");
            if (!wygenGracznr2.loadFromFile("grafika/GraczNr2RozstawiaStatki.png"))
                throw std::runtime_error("Nie udalo sie wczytac GraczNr2RozstawiaStatki.png");
            if (!twojakolej.loadFromFile("grafika/TwojaKolej.png"))
                throw std::runtime_error("Nie udalo sie wczytac TwojaKolej.png");
            if (!wyjscietlo.loadFromFile("grafika/Wyjscie_tlo.png"))
                throw std::runtime_error("Nie udalo sie wczytac Wyjscie_tlo.png");
            if (!wyjscietlo1.loadFromFile("grafika/Wyjscie_tlo1.png"))
                throw std::runtime_error("Nie udalo sie wczytac Wyjscie_tlo1.png");
            if (!music4.loadFromFile("grafika/Music4.png"))
                throw std::runtime_error("Nie udalo sie wczytac Music4.png");
            if (!music4b.loadFromFile("grafika/Music5.png"))
                throw std::runtime_error("Nie udalo sie wczytac Music5.png");
            if (!music5.loadFromFile("grafika/Music6.png"))
                throw std::runtime_error("Nie udalo sie wczytac Music6.png");
            if (!music5b.loadFromFile("grafika/Music6b.png"))
                throw std::runtime_error("Nie udalo sie wczytac Music6b.png");
            if (!zakonczenie1.loadFromFile("grafika/zakonczenie1.png"))
                throw std::runtime_error("Nie udalo sie wczytac zakonczenie1.png");
            if (!zakonczenie2.loadFromFile("grafika/zakonczenie2.png"))
                throw std::runtime_error("Nie udalo sie wczytac zakonczenie2.png");
            if (!zakonczenie3.loadFromFile("grafika/zakonczenie3.png"))
                throw std::runtime_error("Nie udalo sie wczytac zakonczenie3.png");
            if (!zakonczenie4.loadFromFile("grafika/zakonczenie4.png"))
                throw std::runtime_error("Nie udalo sie wczytac zakonczenie4.png");
            if (!wersja.loadFromFile("grafika/version.png"))
                throw std::runtime_error("Nie udalo sie wczytac version.png");
            return true; //jak wszystko jest w porz¹dku, to zwraca true
        }
        catch (const std::exception& e) { //"z³apanie" wyj¹tku i komunikatu z niego; wypisanie wiadomoœci oraz odpowiedniego komunikatu b³êdu
            std::cout << "Wystapil blad podczas wczytywania plikow graficznych: " << e.what() << std::endl;
            return false; //je¿eli coœ siê nie uda³o, to zwraca false
        }
    }

    static bool loadSounds() //metoda ³aduj¹ca dŸwiêki ca³ej gry
    {
        try {
            if (!placeShipSoundBuffer.loadFromFile("muzyka/place.wav")) //za³adowanie dŸwiêku po³o¿enia statku z pliku do bufora (poni¿ej odpowiednio dla reszty buforów)
                throw std::runtime_error("Nie udalo sie wczytac 1"); //obs³uga wyj¹tku (poni¿ej odpowiednio dla reszty wyj¹tków)
            if (!hitSoundBuffer.loadFromFile("muzyka/trafienie.wav"))
                throw std::runtime_error("Nie udalo sie wczytac 2");
            if (!missSoundBuffer.loadFromFile("muzyka/miss.wav"))
                throw std::runtime_error("Nie udalo sie wczytac 3");
            if (!gameOverSoundBuffer.loadFromFile("muzyka/game_over.wav"))
                throw std::runtime_error("Nie udalo sie wczytac 4");
            if (!backgroundMusic.openFromFile("muzyka/background.wav")) //za³adowanie naszej muzyki z t³a z pliku
                throw std::runtime_error("Nie udalo sie wczytac 5");

            placeShipSound.setBuffer(placeShipSoundBuffer); //przypisanie obiektowi bufora po³ozenia statku
            hitSound.setBuffer(hitSoundBuffer); //przypisanie obiektowi bufora trafienia statku
            missSound.setBuffer(missSoundBuffer); //przypisanie obiektowi bufora chybienia
            gameOverSound.setBuffer(gameOverSoundBuffer); //przypisanie obiektowi bufora koñca gry
            
            placeShipSound.setVolume(50); // ustawienie gloœnoœci dŸwiêku po³ozenia statku
            hitSound.setVolume(400); // ustawienie gloœnoœci dŸwiêku trafienia statku
            missSound.setVolume(400); // ustawienie gloœnoœci dŸwiêku chybienia
            gameOverSound.setVolume(400); // ustawienie gloœnoœci dŸwiêku koñca gry
            return true; //jak wszystko jest w porz¹dku, to zwraca true
        }
        catch (const std::exception& e) { //"z³apanie" wyj¹tku i komunikatu z niego; wypisanie wiadomoœci oraz odpowiedniego komunikatu b³êdu
            std::cout << "Wystapil blad podczas wczytywania plikow dzwiekowych: " << e.what() << std::endl;
            return false; //je¿eli coœ siê nie uda³o, to zwraca false
        }
    }
};