#ifndef DRON_HH
#define DRON_HH

#include "ProstopadloscianSCN.hh"
#include "GraniastoslupSCN.hh"

/*!
 * \file  
 * \brief Zawiera definicję klasy Dron
 *
 *  Plik zawiera definicję klasy Dron, sluzacej do
 *  interpretacji zadanego obiektu jako drona zdolnego do bycia przemieszczonym
 *  i obroconym z poziomu metod sceny. Elementami skladowymi drona sa obiekty
 *  klasy \link GraniastoslupSCN \endlink oznaczajace sruby oraz jeden obiekt
 *  klasy \link ProstopadloscianSCN \endlink oznaczajacy rdzen drona.
 *  Dron ponadto jest w stanie wykryc kolizje z dostarczonym mu obiektem klasy
 *  \link ObiektSceny \endlink
 */
/*!
 * \brief Definicja klasy Dron
 *
 *  Definicja klasy Dron, sluzacej do
 *  interpretacji zadanego obiektu jako drona zdolnego do bycia przemieszczonym
 *  i obroconym z poziomu metod sceny. Elementami skladowymi drona sa obiekty
 *  klasy \link GraniastoslupSCN \endlink oznaczajace sruby oraz jeden obiekt
 *  klasy \link ProstopadloscianSCN \endlink oznaczajacy rdzen drona.
 *  Dron ponadto jest w stanie wykryc kolizje z dostarczonym mu obiektem klasy
 *  \link ObiektSceny \endlink
 */

class Dron
{   
    /*!
    *  \brief Pole przechowuje rdzen drona
    * 
    *  Pole przechowuje rdzen drona
    */    
    ProstopadloscianSCN _Rdzen;
    /*!
    *  \brief Pole przechowuje lewa srube drona
    * 
    *  Pole przechowuje lewa srube drona
    */    
    GraniastoslupSCN _LewaSruba;
    /*!
    *  \brief Pole przechowuje prawa srube drona 
    * 
    *  Pole przechowuje prawa srube drona
    */    
    GraniastoslupSCN _PrawaSruba;
    /*!
    * \brief Metoda umozliwia sprawdzenie mozliwosci wystapienia kolizji sruby z przeszkoda
    * 
    * Metoda umozliwia wykrycie kolizji sruby z przeszkoda, wyznaczajac  
    * jej wspolrzedne skrajne i porownujac ze wspolrzednymi skrajnymi przeszkody.
    *  
    * \pre Zarowno sruba jak i przeszkoda musza byc poprawnie zainicjalizowane
    * \param[in] obiekt - referencja do przeszkody
    * \param[in] sruba - referencja do jednej ze srub 
    * \retval true - ruch jest mozliwy
    * \retval false - ruch spowodowalby kolizje
    */
    bool SprawdzMozliwoscRuchuSruby(ObiektSceny &obiekt, GraniastoslupSCN &sruba);
    /*!
    * \brief Metoda umozliwia sprawdzenie mozliwosci wystapienia kolizji rdzenia z przeszkoda
    * 
    * Metoda umozliwia wykrycie kolizji rdzenia z przeszkoda, wyznaczajac  
    * jego wspolrzedne skrajne i porownujac ze wspolrzednymi skrajnymi przeszkody.
    *  
    * \pre Zarowno rdzen jak i przeszkoda musza byc poprawnie zainicjalizowane
    * \param[in] obiekt - referencja do przeszkody 
    * \retval true - ruch jest mozliwy
    * \retval false - ruch spowodowalby kolizje
    */       
    bool SprawdzMozliwoscRuchuRdzenia(ObiektSceny &obiekt);

    public:
    /*!
    *  \brief Metoda umozliwia zewnetrzne odnoszenie sie do obiektu skladowego _Rdzen 
    * 
    *  Metoda umozliwia zewnetrzne odnoszenie sie do obiektu skladowego _Rdzen
    *  \retval _Rdzen - referencja do obiektu klasy \link ProstopadloscianSCN \endlink
    */  
    ProstopadloscianSCN& Wez_Rdzen() {return _Rdzen;}
    /*!
    *  \brief Metoda umozliwia zewnetrzne odnoszenie sie do obiektu skladowego _LewaSruba 
    * 
    *  Metoda umozliwia zewnetrzne odnoszenie sie do obiektu skladowego _LewaSruba
    *  \retval _LewaSruba - referencja do obiektu klasy \link GraniastoslupSCN \endlink
    */      
    GraniastoslupSCN& Wez_Lewa_Srube() {return _LewaSruba;}
    /*!
    *  \brief Metoda umozliwia zewnetrzne odnoszenie sie do obiektu skladowego _PrawaSruba 
    * 
    *  Metoda umozliwia zewnetrzne odnoszenie sie do obiektu skladowego _PrawaSruba
    *  \retval _PrawaSruba - referencja do obiektu klasy \link GraniastoslupSCN \endlink
    */      
    GraniastoslupSCN& Wez_Prawa_Srube() {return _PrawaSruba;}
    /*!
    * \brief Metoda umozliwia sprawdzenie mozliwosci wystapienia kolizji drona z przeszkoda
    * 
    * Metoda umozliwia wykrycie kolizji drona z przeszkoda, wykorzystujac w tym celu
    * metody prywatne \link Dron:SprawdzMozliwoscRuchuSruby \endlink
    * i \link Dron::SprawdzMozliwoscRuchuRdzenia \endlink
    *  
    * \pre Zarowno dron jak i przeszkoda musza byc poprawnie zainicjalizowane
    * \param[in] obiekt - referencja do przeszkody 
    * \retval true - ruch jest mozliwy
    * \retval false - ruch spowodowalby kolizje
    */ 
    bool SprawdzMozliwoscRuchu(ObiektSceny &obiekt);
    /*!
    * \brief Metoda umozliwia zmiane orientacji drona wokol osi OZ
    * 
    * Metoda umozliwia zmiane kata orientacji drona poprzez zmiany katow zapisanych w polach 
    * obiektow skladowych \e _Kat_Orientacji_OZ zwiekszajac ja o wartosc zadana w parametrze 
    * \e kat. Jezeli wartosc kata orientacji wyniesie 360 lub -360, zostana one 
    * wyzerowana w celu zmniejszenia bledow dokladnosci obliczen.
    *  
    * \param[in] kat - Kat o jaki zmieniona zostanie orientacja OZ kazdego z obiektu skladowych
    */    
    void Zmien_o_kat(unsigned int kat);

    /*!
    * \brief Metoda umozliwia zmiane orientacji srub wokol osi OX
    * 
    * Metoda umozliwia zmiane kata orientacji srub zapisanego w ich polach \e _Kat_Orientacji_OX
    * zwiekszajac ja o wartosc zadana w parametrze \e kat. Jezeli wartosc kata orientacji
    * wyniesie 360 lub -360, zostaje ona wyzerowana w celu zmniejszenia bledow 
    * dokladnosci obliczen.
    *  
    * \param[in] kat - Kat o jaki zmieniona zostanie orientacja OX kazdej ze srub
    */      
    void Zmien_o_kat_wlasny(unsigned int kat);
    /*!
    * \brief Metoda umozliwia zmiane polozenia drona
    * 
    * Metoda umozliwia zmiane wektorow polozenia bryl skladowych zapisanych w ich 
    * polach \e _Wek_Translacji zwiekszajac ja o wektor zadany w parametrze \e Translacja
    *  
    * \param[in] Translacja - Wektor o jaki zwiekszony zostanie wektor 
    *                         translacji kazdego z elementow skladowych
    */      
    void Zmien_o_translacje(Wektor3D Translacja);
    /*!
    * \brief Realizuje przeksztalcenie wspolrzednych lokalnych drona do ukladu globalnego
    * 
    * Realizuje przeksztalcenie wspolrzednych lokalnych kazdego z elementow skladowych drona
    * do ukladu globalnego biorac pod uwage ich kat orientacji oraz wektory translacji
    * 
    * \pre Obiekty musza byc poprawnie zainicjalizowane
    * \retval true  - operacja przebiegla pomyslnie
    * \retval false - nie udalo sie okreslic wspolrzednych globalnych - dla przynajmniej jednego obiektu wystapil
    *                 blad prawidlowego odczytania wspolrzednych z pliku \e _Plik_Wsp_Lokalne lub blad
    *                 zapisu do pliku \e _Plik_Wsp_Globalne 
    */    
    bool ObliczGlobalne() const;


};
#endif