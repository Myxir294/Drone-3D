#ifndef GRANIASTOSLUP_HH
#define GRANIASTOSLUP_HH

#include "ObiektSceny.hh"

/*!
 * \file  
 * \brief Zawiera definicję klasy Graniastoslup
 *
 *  Plik zawiera definicję klasy Graniastoslup, sluzacej do
 *  interpretacji zadanego obiektu jako graniastoslupa majacego
 *  okreslone wspolrzedne w ukladzie kartezjanskim. Ponadto obiekt
 *  zapamietuje wartosc swojego promienia oraz lokalne polozenie swojego
 *  srodka. 
 */
/*!
 * \brief Graniastoslup jako bryla przestrzenna o promieniu i srodku lokalnym
 *
 *  Definicja klasy Graniastoslup, sluzacej do
 *  interpretacji zadanego obiektu jako graniastoslupa majacego
 *  okreslone wspolrzedne w ukladzie kartezjanskim. Ponadto obiekt
 *  zapamietuje wartosc swojego promienia oraz lokalne polozenie swojego
 *  srodka. 
 */
class Graniastoslup: public ObiektSceny
{
    /*!
    *  \brief Pole przechowuje dlugosc promienia
    * 
    *  Pole przechowuje dlugosc promienia bryly
    */
    unsigned int _promien;

    /*!
    *  \brief Pole przechowuje wspolrzedne srodka
    * 
    *  Pole przechowuje pierwotne wspolrzedne srodka bryly
    */
    Wektor3D _srodek_lok;

    public:
    /*!
    *  \brief Konstruktor bezparametryczny
    * 
    *  Konstruktor bezparametryczny inicjalizujacy poczatkowa dlugosc promienia
    */    
    Graniastoslup(){_promien = 0;}
    /*!
    *  \brief Metoda umozliwia okreslenie promienia i srodka
    * 
    *  Metoda umozliwia wyznaczenie wspolrzednych srodka lokalnego
    *  oraz dlugosci promienia bryly, a nastepnie zapamietanie
    *  ich wartosci w polach obiektu
    * \pre Wspolrzedne obiektu musza byc wczesniej poprawnie zapisane
    *      w pliku, ktorego nazwa zapisana jest przez 
    *      pole \e _Plik_Wsp_Lokalne
    *  
    */    
    void Wyznacz_Promien_i_Srodek();

    /*!
    * \brief Metoda umozliwia pobranie dlugosci promienia 
    * 
    * Metoda umozliwia pobranie wartosci promienia
    * \pre Wartosc promienia musi byc wczesniej wyliczona 
    * \retval Wartosc \e _promien
    */    
    unsigned int const PodajPromien() const {return _promien;}

    /*!
    * \brief Metoda umozliwia pobranie wspolrzednych srodka 
    * 
    * Metoda umozliwia pobranie wartosci wspolrzednych srodka lokalnego bryly 
    * \retval Wektor3D \e _srodek_lok
    */    
    Wektor3D const PodajSrodekLok() const {return _srodek_lok;}

    /*!
    * \brief Metoda umozliwia wyznaczenie wspolrzednych skrajnych bryly
    * 
    * Metoda umozliwia wyznaczenie wspolrzednych skrajnych bryly, nadpisujac
    * w odpowiedni sposob metode \link ObiektSceny::WyznaczWsp() \endlink 
    * 
    * \pre Obiekt musi miec poprawnie zadane nazwy plikow ze wspolrzednymi 
    * \retval true - proces przebiegł pomyślnie
    * \retval false - nie udało sie wyznaczyc wspolrzednych skrajnych
    */ 
    virtual bool WyznaczWsp() override;        
};


#endif