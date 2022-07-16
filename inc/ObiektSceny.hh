#ifndef OBIEKTSCENY_HH
#define OBIEKTSCENY_HH

#include "typy_danych.hh"

#include <string>
#include <fstream>

/*!
 * \file  
 * \brief Zawiera definicję klasy ObiektSceny
 *
 *  Plik zawiera definicję klasy ObiektSceny, sluzacej do ogólnenj
 *  interpretacji obiektów przestrzennych, mających okreslone 
 *  wspolrzedne w ukladzie kartezjanskim. Ponadto obiekt zapamietuje 
 *  wartosci swoich wspolrzednych skrajnych w celu umozliwienia 
 *  bycia wykorzystanym do wykrycia kolizji. Klasa stanowi klase
 *  bazowa dla kazdej bryly reprezentowanej w pozostalej czesci programu.
 */
/*!  
 * \brief Definicja klasy ObiektSceny
 *
 *  Definicję klasy ObiektSceny, sluzacej do ogólnej
 *  interpretacji obiektów przestrzennych, mających okreslone 
 *  wspolrzedne w ukladzie kartezjanskim. Ponadto obiekt zapamietuje 
 *  wartosci swoich wspolrzednych skrajnych w celu umozliwienia 
 *  bycia wykorzystanym do wykrycia kolizji. Klasa stanowi klase
 *  bazowa dla kazdej bryly reprezentowanej w pozostalej czesci programu.
 */
class ObiektSceny
{
    /*!
    *  \brief Pole przechowuje nazwe pliku z danymi lokalnymi
    * 
    *  Pole przechowuje nazwe pliku z danymi lokalnymi
    */       
    std::string _Plik_Wsp_Lokalne;
    /*!
    *  \brief Pole przechowuje wspolrzedne maksymalne
    * 
    *  Pole przechowuje wspolrzedne maksymalne, tj. najbardziej wysuniete
    *  w strone dodatniej czesci kazdej osi ukladu
    */
    Wektor3D _Wsp_Max;
    /*!
    *  \brief Pole przechowuje wspolrzedne minimalne
    * 
    *  Pole przechowuje wspolrzedne minimalne, tj. najbardziej wysuniete
    *  w strone ujemnej czesci kazdej osi ukladu
    */    
    Wektor3D _Wsp_Min;

    public:
    /*!
    *  \brief Konstruktor bezparametryczny
    * 
    *  Konstruktor bezparametryczny wyswietlajacy komunikat o utworzeniu obiektu,
    *  w celu ulatwienia kontrolowania poprawnego wykorzystania pamieci
    */ 
    ObiektSceny() {std::cout << "Stworzenie obiektu sceny" << std::endl;}
    /*!
    *  \brief Destruktor
    * 
    *  Destruktor wyswietlajacy komunikat o usunieciu obiektu,
    *  w celu ulatwienia kontrolowania poprawnego wykorzystania pamieci
    */ 
    virtual ~ObiektSceny() {std::cout << "Usuniecie obiektu sceny" << std::endl;}

    /*!
    * \brief Pierwotna wersja metodu umozliwiajacej wyznaczenie wspolrzednych skrajnych bryly
    * 
    * Metoda umozliwia wyznaczenie wspolrzednych skrajnych bryly. W postaci
    * zapisanej w tej klasie nie posiada ona kodu, gdyz nigdy nie bedzie ona wywolywana
    * jako metoda samoistniejącej klasy bazowej - w odpowiednich klasach pochodnych jest 
    * ona we wlasciwy sposob nadpisywana, aby poprawnie wyznaczac wspolrzedne skrajne
    * dla roznych rodzajow bryl
    * 
    * \pre Obiekt musi miec poprawnie zadane nazwy plikow ze wspolrzednymi 
    * \retval true - proces przebiegł pomyślnie
    * \retval false - nie udało sie wyznaczyc wspolrzednych skrajnych
    */   
    virtual bool WyznaczWsp() = 0;
    /*!
    *  \brief Metoda umozliwia przypisanie obiektowi pliku
    * 
    *  Metoda umozliwia przypisanie obiektowi pliku ze wspolrzednymi lokalnymi
    * 
    *  \param[in] NazwaPliku - Nazwa pliku ze wspolrzednymi lokalnymi
    *  
    */
    void WybierzPlikLok(const char *NazwaPliku){_Plik_Wsp_Lokalne = NazwaPliku;}
    /*!
    * \brief Metoda umozliwia pobranie nazwy przypisanego pliku
    * 
    *   Metoda umozliwia pobranie nazwy przypisanego pliku, w ktorym  
    *   znajduja sie zadane wspolrzedne obiektu
    *   \pre Nazwa pliku lokalnego musi byc wczesniej wybrana 
    *   \retval Parametr \e _Plik_Wsp_Lokalne                                  
    */   
    const std::string PodajNazwePlikuLok() const {return _Plik_Wsp_Lokalne;}
    /*!
    * \brief Metoda umozliwia pobranie wartosci wspolrzednych maksymalnych 
    * 
    * Metoda umozliwia pobranie wartosci wspolrzednych maksymalnych
    * \pre Wartosc wspolrzednych musi byc wczesniej wyliczona
    * \retval Wektor3D \e _Wsp_Max
    */
    Wektor3D const PodajWspMax() const {return _Wsp_Max;}
    /*!
    * \brief Metoda umozliwia pobranie i modyfikacje wartosci wspolrzednych maksymalnych 
    * 
    * Metoda umozliwia pobranie i modyfikacje wartosci wspolrzednych maksymalnych
    * \pre Wartosc wspolrzednych musi byc wczesniej wyliczona
    * \retval Wektor3D& \e _Wsp_Max
    */    
    Wektor3D& PodajWspMax() {return _Wsp_Max;}
    /*!
    * \brief Metoda umozliwia pobranie wartosci wspolrzednych minimalnych 
    * 
    * Metoda umozliwia pobranie wartosci wspolrzednych minimalnych
    * \pre Wartosc wspolrzednych musi byc wczesniej wyliczona
    * \retval Wektor3D \e _Wsp_Min
    */    
    Wektor3D const PodajWspMin() const {return _Wsp_Min;}
    /*!
    * \brief Metoda umozliwia pobranie i modyfikacje wartosci wspolrzednych minimalnych 
    * 
    * Metoda umozliwia pobranie i modyfikacje wartosci wspolrzednych minimalnych
    * \pre Wartosc wspolrzednych musi byc wczesniej wyliczona
    * \retval Wektor3D& \e _Wsp_Min
    */      
    Wektor3D& PodajWspMin() {return _Wsp_Min;}
};

#endif