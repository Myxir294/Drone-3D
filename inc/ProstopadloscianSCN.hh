#ifndef PROSTOPADLOSCIANSCN_HH
#define PROSTOPADLOSCIANSCN_HH

#include "Prostopadloscian.hh"

/*!
 * \file  
 * \brief Zawiera definicję klasy ProstopadloscianSCN
 *
 *  Plik zawiera definicję klasy ProstopadloscianSCN, sluzacej do
 *  interpretacji zadanego prostopadloscianu jako obiektu rozbudowanego
 *  o mozliwosc okreslenia orientacji i przesuniecia w ukladzie globalnym
 */
/*!  
 * \brief ProstopadloscianSCN jako Prostopadloscian w ukladzie globalnym
 *
 *  Definicja klasy ProstopadloscianSCN, sluzacej do
 *  interpretacji zadanego prostopadloscianu jako obiektu rozbudowanego
 *  o mozliwosc okreslenia orientacji i przesuniecia w ukladzie globalnym
 */
class ProstopadloscianSCN: public Prostopadloscian
{
    /*!
    *  \brief Pole przechowuje nazwe pliku z danymi globalnymi
    * 
    *  Pole przechowuje nazwe pliku z danymi globalnymi
    */
    std::string _Plik_Wsp_Globalne;

    /*!
    *  \brief Pole przechowuje miare kata orientacji
    * 
    *  Pole przechowuje miare kata orientacji bryly okreslonego w stopniach
    */    
    int _Kat_Orientacji;

    /*!
    *  \brief Pole przechowuje wektor translacji bryly
    * 
    *  Pole przechowuje wektor translacji bryly - domyslnie wektor
    *  zerowy
    */     
    Wektor3D _Wek_Translacji;

    public:
    /*!
    *  \brief Konstruktor obiektu ProstopadloscianSCN
    * 
    *  Konstruktor bezparametryczny obiektu ProstopadloscianSCN,
    *  ustawiajacy domyslna wartosc kata orientacji bryly na 0
    */   
    ProstopadloscianSCN(){_Kat_Orientacji = 0;}
    /*!
    *  \brief Metoda umozliwia przypisanie obiektowi pliku ze wspolrzednymi globalnymi 
    * 
    *  Metoda umozliwia przypisanie obiektowi pliku ze wspolrzednymi globalnymi
    * 
    *  \param[in] NazwaPliku - Nazwa pliku ze wspolrzednymi globalnymi
    *  
    */
    void WybierzPlikGlob(const char *NazwaPliku){_Plik_Wsp_Globalne = NazwaPliku;}

    /*!
    * \brief Metoda umozliwia pobranie nazwy przypisanego pliku ze wspolrzednymi globalnymi
    * 
    *   Metoda umozliwia pobranie nazwy przypisanego pliku, w ktorym  
    *   beda znajdowac sie wyliczone wspolrzedne globalne obiektu
    * \pre Nazwa pliku ze wspolrzednymi globalnymi musi byc wczesniej okreslona
    * \retval Parametr \e _Plik_Wsp_Globalne                                  
    */     
    const std::string PodajNazwePlikuGlob() const {return _Plik_Wsp_Globalne;}

    /*!
    * \brief Metoda umozliwia wyznaczenie obecnych wspolrzednych skrajnych bryly
    * 
    * Metoda umozliwia wyznaczenie obecnych wspolrzednych skrajnych bryly, nadpisujac
    * w odpowiedni sposob metode \link ObiektSceny::WyznaczWsp() \endlink 
    * 
    * \pre Obiekt musi miec poprawnie zadane nazwy plikow ze wspolrzednymi 
    * \retval true - proces przebiegł pomyślnie
    * \retval false - nie udało sie wyznaczyc wspolrzednych skrajnych
    */
    virtual bool WyznaczWsp() override;

    /*!
    * \brief Realizuje przeksztalcenie wspolrzednych lokalnych do ukladu globalnego
    * 
    * Realizuje przeksztalcenie wspolrzednych lokalnych do ukladu globalnego biorac
    * pod uwage kat orientacji oraz wektor translacji bryly
    * 
    * \pre Obiekt musi miec poprawnie zadane nazwy plikow ze wspolrzednymi
    * \retval true  - operacja przebiegla pomyslnie
    * \retval false - nie udalo sie okreslic wspolrzednych globalnych - blad prawidlowego
    *                 odczytania wspolrzednych z pliku \e _Plik_Wsp_Lokalne lub blad
    *                 zapisu do pliku \e _Plik_Wsp_Globalne 
    */
    bool ObliczGlobalne() const;

    /*!
    *  \brief Metoda umozliwia przypisanie obiektowi dwoch plikow
    * 
    *  Metoda umozliwia przypisanie obiektowi pliku ze wspolrzednymi
    *  poczatkowymi (lokalnymi) oraz pliku w ktorym zostana zapisane 
    *  wspolrzedne przeksztalcone do ukladu globalnego (globalne). 
    *  Wykorzystuje w tym celu metody 
    * \link ObiektSceny::WybierzPlikLok \endlink
    * \link ProstopadloscianSCN::WybierzPlikGlob \endlink
    * \link ProstopadloscianSCN::ObliczGlobalne \endlink
    * 
    *  \param[in] NazwaPlikuWe - Nazwa pliku ze wspolrzednymi lokalnymi
    *  \param[in] NazwaPlikuWy - Nazwa pliku ze wspolrzednymi lokalnymi
    *  \retval true - operacja przebiegla pomyslnie
    *  \retval false - metoda \link ProstopadloscianSCN::ObliczGlobalne \endlink
    *                  nie byla w stanie poprawnie wykonac operacji okreslenia
    *                  i zapisania wspolrzednych globalnych
    */    
    bool WybierzPliki(const char *NazwaPlikuWe, const char *NazwaPlikuWy);

    /*!
    * \brief Metoda umozliwia zmiane orientacji bryly wokol osi OZ
    * 
    * Metoda umozliwia zmiane kata orientacji bryly zapisanego w polu \e _Kat_Orientacji
    * zwiekszajac ja o wartosc zadana w parametrze \e kat. Jezeli wartosc kata orientacji
    * wyniesie 360 lub -360, zostaje ona wyzerowana w celu zmniejszenia bledow 
    * dokladnosci obliczen
    *  
    * \param[in] kat - Kat o jaki zmieniona zostanie orientacja bryly
    */  
    void Zmien_o_kat(int kat);

    /*!
    * \brief Metoda umozliwia zmiane polozenia bryly 
    * 
    * Metoda umozliwia zmiane wektora polozenia bryly zapisanego w polu \e _Wek_Translacji
    * zwiekszajac ja o wektor zadany w parametrze \e Translacja
    *  
    * \param[in] Translacja - Wektor o jaki zwiekszony zostanie wektor translacji bryly
    */     
    void Zmien_o_translacje(Wektor3D Translacja){_Wek_Translacji = _Wek_Translacji + Translacja;}

    /*!
    * \brief Metoda umozliwia pobranie wartosci kata orientacji bryly 
    * 
    * Metoda umozliwia pobranie wartosci okreslonego kata orientacji bryly
    * \retval Wartosc \e _Kat_Orientacji
    */

    int const PodajKatOrientacji() const {return _Kat_Orientacji;}
    /*!
    * \brief Metoda umozliwia pobranie wartosci wektora polozenia bryly 
    * 
    * Metoda umozliwia pobranie wartosci okreslonego wektora polozenia bryly
    * \retval Wektor3D \e _Wek_Translacji
    */      
    Wektor3D const PodajPolozenie() const {return _Wek_Translacji;}

};

#endif