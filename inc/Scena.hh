#ifndef SCENA_HH
#define SCENA_HH

#include "Dron.hh"
#include "lacze_do_gnuplota.hh"
#include "Powierzchnia.hh"
#include "PowierzchniaFalowana.hh"
#include "Pret.hh"


#include <unistd.h>


/*!
 * \file  
 * \brief Zawiera definicję klasy Scena
 *
 *  Plik zawiera definicję klasy Scena, sluzacej do zarzadzania
 *  graficznymi interpretacjami obiektow wykorzystywanych przez
 *  program.
 */

/*!  
 * \brief Scena jako klasa zarzadzajaca obiektami graficznymi
 *
 *  Definicja klasy Scena, sluzacej do zarzadzania graficznymi 
 *  interpretacjami obiektow wykorzystywanych przez program.
 */

class Scena
{   
    /*!
    *  \brief Pole przechowuje zmienna umozliwiajaca przekazanie danych do programu \e gnuplot 
    * 
    *  Pole przechowuje zmienna umozliwiajaca przekazywanie danych rysunku do programu \e gnuplot
    *  za pomoca klasy \link PzG::LaczeDoGNUPlota \endlink
    */
    PzG::LaczeDoGNUPlota  Lacze;
    /*!
    *  \brief Pole przechowuje zmienna interpretujaca ruchomego drona 
    * 
    *  Pole przechowuje zmienna interpretujaca ruchomego drona za pomoca klasy \link Dron \endlink
    */ 
    Dron Dron1;

    /*!
    *  \brief Pole przechowuje zmienna interpretujaca powierzchnie wody 
    * 
    *  Pole przechowuje zmienna interpretujaca powierzchnie wody za pomoca klasy \link PowierzchniaFalowana \endlink
    */     
    PowierzchniaFalowana Woda;
    /*!
    *  \brief Pole przechowuje liste tworzonych dynamicznie przeszkód
    * 
    *  Pole przechowuje liste tworzonych dynamicznie przeszkod za pomoca obiektu typu std::list
    *  Lista okreslona jest dla klasy \link ObiektSceny \endlink bedacej klasa bazowa kazdego rodzaju
    *  przeszkody - podczas dynamicznego dodawania kolejnych obiektow nastepuje rzutowanie w gore na klase bazowa
    */
    std::list <ObiektSceny*> Lista;

    /*!
    *  \brief Metoda umozliwia obliczenie wektora przesuniecia bryly 
    * 
    *  Metoda umozliwia obliczenie wektora przesuniecia bryly, uwzgledniajac
    *  jej obecny kat orientacji oraz wskazany kat wynurzenia/zanurzenia
    * 
    *  \param[in] dlugosc - zadana dlugosc wektora przesuniecia
    *  \param[in] kat_z - zadana kat wynurzenia/zanurzenia
    *  \param[in] kat_orientacji - aktualny kat orientacji bryly wokol osi OZ
    *  \retval Wektor3D - okreslajacy zmiane polozenia 
    *  
    */
    Wektor3D ObliczWektorPrzesuniecia(unsigned int dlugosc, int kat_z, int kat_orientacji) const;
    /*!
    *  \brief Metoda umozliwia narysowanie obecnego stanu obiektow graficznych 
    * 
    *  Metoda umozliwia narysowanie obecnego stanu obiektow graficznych za pomoca
    *  metody \link PzG::LaczeDoGNUPlota::Rysuj \endlink wykorzystujacej w tym celu 
    *  dane przekazane do programu \e gnuplot
    */
    void Rysuj_Scene() {Lacze.Rysuj();}

    /*!
    * \brief Realizuje sprawdzenie stopnia wynurzenia wskazanej ruchomej bryly
    * 
    * Realizuje sprawdzenie stopnia wynurzenia wskazanej ruchomej bryly poprzez
    * porownanie wspolrzednych skrajnych bryly po translacji oraz powierzchni falowanej oznaczajacej
    * wode
    * 
    * \pre Obiekty musza zostac wczesniej poprawnie zainicjalizowane
    * \pre Sprawdzenie wynurzenia powinno wystapic po zarejestrowaniu bezkolizyjnej translacji 
    * \param[in] Dron - referencja do drona, umozliwiajaca sprawdzenie jego polozenia
    * \retval true  - zadany ruch spowodowalby wydostanie sie ponad maksymalne wynurzenie
    * \retval false - zadany ruch jest dopuszczalny
    */  
    bool SprawdzWynurzenie(Dron &Element) const;

    public: 
    /*!
    *  \brief Metoda umozliwia zewnetrzne odnoszenie sie do obiektu skladowego Dron1 
    * 
    *  Metoda umozliwia zewnetrzne odnoszenie sie do obiektu skladowego Dron1
    *  \retval Dron1 - referencja do obiektu Dron1 klasy \link Dron \endlink
    */       
    Dron& Wez_Drona1() {return Dron1;}
    /*!
    * \brief Metoda umozliwia dodanie do listy przeszkod elementu klasy \link Powierzchnia \endlink
    * 
    * Metoda umozliwia dynamiczne nieruchomego elementu skladowego sceny, 
    * klasy \link Powierzchnia \endlink, przypisujac mu odpowiedni plik oraz
    * przekazujac nazwe tego pliku do programu \e gnuplot. 
    * Obiekt ten zostaje nastepnie zapamietany w liscie przeszkod.
    * \param[in] - NazwaPliku - nazwa pliku z danymi lokalnymi dodawanej powierzchni
    * \retval true  - element zostal wczytany poprawnie
    * \retval false - nie udalo sie poprawnie wczytac elementu - plik z danymi
    *                 jest niepoprawny lub nie istnieje
    */
    bool Dodaj_Powierzchnie(const char *NazwaPliku);

    /*!
    * \brief Metoda umozliwia wczytanie powierzchni wody, klasy \link PowierzchniaFalowana \endlink
    * 
    * Metoda umozliwia wczytanie elementu sladowego Woda, klasy \link PowierzchniaFalowana \endlink, 
    * przypisujac mu odpowiedni plik oraz przekazujac nazwe tego pliku do programu \e gnuplot
    * \param[in] - NazwaPliku - nazwa pliku z danymi lokalnymi dodawanej powierzchni
    * \retval true  - element zostal wczytany poprawnie
    * \retval false - nie udalo sie poprawnie wczytac elementu - plik z danymi
    *                 jest niepoprawny lub nie istnieje
    */    
    bool Dodaj_Powierzchnie_Falowana(const char *NazwaPliku);
    /*!
    * \brief Metoda umozliwia dodanie do listy przeszkod elementu klasy \link Prostopadloscian \endlink
    * 
    * Metoda umozliwia dynamiczne nieruchomego elementu skladowego sceny, 
    * klasy \link Prostopadloscian \endlink, przypisujac mu odpowiedni plik oraz
    * przekazujac nazwe tego pliku do programu \e gnuplot. 
    * Obiekt ten zostaje nastepnie zapamietany w liscie przeszkod.
    * \param[in] - NazwaPliku - nazwa pliku z danymi lokalnymi dodawanej powierzchni
    * \retval true  - element zostal wczytany poprawnie
    * \retval false - nie udalo sie poprawnie wczytac elementu - plik z danymi
    *                 jest niepoprawny lub nie istnieje
    */        
    bool Dodaj_Bryle(const char *NazwaPliku);

    /*!
    * \brief Metoda umozliwia dodanie do listy przeszkod elementu klasy \link Pret \endlink
    * 
    * Metoda umozliwia dynamiczne nieruchomego elementu skladowego sceny, 
    * klasy \link Pret \endlink, przypisujac mu odpowiedni plik oraz
    * przekazujac nazwe tego pliku do programu \e gnuplot. 
    * Obiekt ten zostaje nastepnie zapamietany w liscie przeszkod.
    * \param[in] - NazwaPliku - nazwa pliku z danymi lokalnymi dodawanej powierzchni
    * \retval true  - element zostal wczytany poprawnie
    * \retval false - nie udalo sie poprawnie wczytac elementu - plik z danymi
    *                 jest niepoprawny lub nie istnieje
    */     
    bool Dodaj_Pret(const char *NazwaPliku);

    /*!
    *  \brief Metoda umozliwia zwolnienie pamieci listy 
    * 
    *  Metoda umozliwia zwolnienie pamieci listy, usuwajac dynamicznie po kolei
    *  wszystkie jej obiekty, wykorzystujac petle zakresu
    */ 
    void WyczyscListe(){for (ObiektSceny* ptr: Lista) delete ptr;}

    /*!
    * \brief Metoda umozliwia wczytanie drona, klasy \link Dron \endlink
    * Metoda umozliwia wczytanie elementu sladowego dron, klasy \link Dron \endlink, 
    * przypisujac mu odpowiednie pliki oraz przekazujac nazwy tych pliku do programu \e gnuplot
    * 
    * \param[in] - Element - referencja do dodawanego drona
    * \param[in] - NazwaPlikuWeRdzen - nazwa pliku z danymi lokalnymi rdzenia drona
    * \param[in] - NazwaPlikuWyRdzen - nazwa pliku zapisu wspolrzedznych globalnych rdzenia drona
    * \param[in] - NazwaPlikuWeLSruba - nazwa pliku z danymi lokalnymi lewej sruby drona
    * \param[in] - NazwaPlikuWyLSruba - nazwa pliku zapisu wspolrzedznych globalnych lewej sruby drona
    * \param[in] - NazwaPlikuWePSruba - nazwa pliku z danymi lokalnymi prawej sruby drona
    * \param[in] - NazwaPlikuWyPSruba - nazwa pliku zapisu wspolrzedznych globalnych prawej sruby drona
    * \retval true  - element zostal wczytany poprawnie
    * \retval false - nie udalo sie poprawnie wczytac elementu - przynajmniej jeden plik z danymi
    *                 jest niepoprawny lub nie istnieje
    */ 
    bool Dodaj_Drona(Dron &Element, 
                     const char *NazwaPlikuWeRdzen,
                     const char *NazwaPlikuWeLSruba,
                     const char *NazwaPlikuWePSruba, 
                     const char *NazwaPlikuWyRdzen,
                     const char *NazwaPlikuWyLSruba,
                     const char *NazwaPlikuWyPSruba
                    );

    /*!
    * \brief Metoda umozliwia inicjalizacje sceny
    * 
    * Metoda umozliwia inicjalizacje sceny, wczytujac elementy okreslone w polach klasy, 
    * dodajac do listy przekszód po jednym przykladzie kazdej przeszkody
    * oraz przekazujac programowi \e gnuplot nazwy plikow, na podstawie ktorych rysowana
    * bedzie scena. W przypadku poprawnej inicjalizacji program \e gnuplot rozpoczyna
    * prace od narysowania graficznej interpretacji poczatkowego stanu sceny. 
    * 
    * \retval true  - inicjalizacja przebiegla pomyslnie
    * \retval false - nie udalo sie poprawnie wczytac elementow sceny
    */    
    bool InicjalizujScene();

    /*!
    * \brief Metoda umozliwia animowany obrot drona
    * 
    * Metoda umozliwia animowany obrot drona z wykorzystaniem zdefiniowanych
    * wartosci DOKLADNOSC_KATA_ODSWIEZANIA (kat pojedynczej fazy ruchu, w stopniach) 
    * oraz CZAS_ODSWIEZANIA (czas miedzy kazda z faz ruchu, w ms)
    * \param[in] - Element - referencja do obracanego obiektu
    * \param[in] - kat - kat o jaki dron ma sie obrocic
    * \retval true  - obrot udalo sie wykonac poprawnie
    * \retval false - nie udalo sie poprawnie wykonac operacji - wystapil blad
    *                 wyliczenia lub obrot spowodowalby kolizje z przeszkoda
    */    
    bool Animowany_Obrot_Bryly(Dron &Element, int kat);

    /*!
    * \brief Metoda umozliwia animowany ruch drona
    * 
    * Metoda umozliwia animowany ruch drona z wykorzystaniem zdefiniowanych
    * wartosci DOKLADNOSC_WEKTORA_ODSWIEZANIA (dlugosc wektora pojedynczej fazy ruchu) 
    * oraz CZAS_ODSWIEZANIA (czas miedzy kazda z faz ruchu, w ms). Przed kazda
    * faza ruchu metoda sprawdza, czy nie spowodowalaby ona uderzenia o przeszkode lub
    * nadmiernego wynurzenia. W pierwszym przypadku ruch zostaje przerwany, a w drugim
    * ruch jest kontynuowany z zachowaniem stalej wysokosci drona.
    * \param[in] - Element - referencja do przesuwanego obiektu
    * \param[in] - kat_z - kat wynurzenia/zanurzenia drona
    * \param[in] - dlugosc - dlugosc zadanego ruchu
    * \retval true  - ruch udalo sie wykonac poprawnie
    * \retval false - nie udalo sie poprawnie wykonac operacji lub operacja spowodowalaby
    *                 kolizje z dnem
    */
    bool Animowana_Translacja_Bryly(Dron &Element, int kat_z, unsigned int dlugosc);
    
    
};


#endif