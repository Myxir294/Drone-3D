#ifndef GRANIASTOSLUPSCN_HH
#define GRANIASTOSLUPSCN_HH

#include "Graniastoslup.hh"


/*!
 * \file  
 * \brief Zawiera definicję klasy GraniastoslupSCN
 *
 *  Plik zawiera definicję klasy GraniastoslupSCN, sluzacej do
 *  interpretacji zadanego graniastoslupa jako obiektu rozbudowanego
 *  o mozliwosc okreslenia orientacji i przesuniecia w ukladzie globalnym
 */
/*!  
 * \brief GraniastoslupSCN jako Graniastoslup w ukladzie globalnym
 *
 *  Definicja klasy GraniastoslupSCN, sluzacej do
 *  interpretacji zadanego graniastoslupa jako obiektu rozbudowanego
 *  o mozliwosc okreslenia orientacji i przesuniecia w ukladzie globalnym
 */

class GraniastoslupSCN: public Graniastoslup 
{
    /*!
    *  \brief Pole przechowuje nazwe pliku z danymi globalnymi
    * 
    *  Pole przechowuje nazwe pliku z danymi globalnymi
    */
    std::string _Plik_Wsp_Globalne;
    /*!
    *  \brief Pole przechowuje miare kata orientacjiOZ
    * 
    *  Pole przechowuje miare kata orientacjiOZ bryly okreslonego w stopniach
    */ 
    int _Kat_Orientacji_OZ;
    /*!
    *  \brief Pole przechowuje miare kata orientacjiOX
    * 
    *  Pole przechowuje miare kata orientacjiOX bryly okreslonego w stopniach
    */     
    int _Kat_Orientacji_OX;

    /*!
    *  \brief Pole przechowuje wektor translacji bryly
    * 
    *  Pole przechowuje wektor translacji bryly - domyslnie wektor
    *  zerowy
    */     
    Wektor3D _Wek_Translacji;
    /*!
    *  \brief Zmiana kata wlasnego, tj. \param _Kat_Orientacji_OX 
    * 
    *  Metoda umozliwia obrot graniastoslupa wokol osi OX
    */    
    void Zmien_kat_wlasny(){_Kat_Orientacji_OX += DOKLADNOSC_KATA_ODSWIEZANIA;}

    public:
    /*!
    *  \brief Konstruktor obiektu GraniastoslupSCN
    * 
    *  Konstruktor bezparametryczny obiektu GraniastoslupSCN,
    *  ustawiajacy domyslna wartosc katow orientacji bryly na 0
    */     
    GraniastoslupSCN();

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
    * \link GraniastoslupSCN::WybierzPlikGlob \endlink
    * \link GraniastoslupSCN::ObliczGlobalne \endlink
    * 
    *  \param[in] NazwaPlikuWe - Nazwa pliku ze wspolrzednymi lokalnymi
    *  \param[in] NazwaPlikuWy - Nazwa pliku ze wspolrzednymi lokalnymi
    *  \retval true - operacja przebiegla pomyslnie
    *  \retval false - metoda \link GraniastoslupSCN::ObliczGlobalne \endlink
    *                  nie byla w stanie poprawnie wykonac operacji okreslenia
    *                  i zapisania wspolrzednych globalnych
    */       
    bool WybierzPliki(const char *NazwaPlikuWe, const char *NazwaPlikuWy, unsigned int numer);

    /*!
    * \brief Metoda umozliwia zmiane orientacji bryly wokol osi OZ
    * 
    * Metoda umozliwia zmiane kata orientacji bryly zapisanego w polu \e _Kat_Orientacji_OZ
    * zwiekszajac ja o wartosc zadana w parametrze \e kat. Jezeli wartosc kata orientacji
    * wyniesie 360 lub -360, zostaje ona wyzerowana w celu zmniejszenia bledow 
    * dokladnosci obliczen
    *  
    * \param[in] kat - Kat o jaki zmieniona zostanie orientacja bryly
    */    
    void Zmien_o_kat(int kat);
    /*!
    * \brief Metoda umozliwia zmiane orientacji bryly wokol osi OX
    * 
    * Metoda umozliwia zmiane kata orientacji bryly zapisanego w polu \e _Kat_Orientacji_OX
    * zwiekszajac ja o wartosc zadana w parametrze \e kat. Jezeli wartosc kata orientacji
    * wyniesie 360 lub -360, zostaje ona wyzerowana w celu zmniejszenia bledow 
    * dokladnosci obliczen
    *  
    * \param[in] kat - Kat o jaki zmieniona zostanie orientacja bryly
    */     
    void Zmien_o_kat_wlasny(int kat);
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
    * \retval Wartosc \e _Kat_Orientacji_OZ
    */
    int const PodajKatOrientacji() const {return _Kat_Orientacji_OZ;}

    /*!
    * \brief Metoda umozliwia pobranie wartosci wektora polozenia bryly 
    * 
    * Metoda umozliwia pobranie wartosci okreslonego wektora polozenia bryly
    * \retval Wektor3D \e _Wek_Translacji
    */     
    Wektor3D const PodajPolozenie() const {return _Wek_Translacji;}

};

#endif