#ifndef SMACIERZ_HH
#define SMACIERZ_HH

#include <iostream>
#include "SWektor.hh"
/*!
 * \file
 * \brief Plik zawiera definicje szablonu macierzy kwadratowej
 * 
 * Plik zawiera szablon klasy modelujacej pojęcie macierzy jako 
 * jednowymiarowej tablicy wektorów o wielkości "Wymiar". Zawiera ona metody 
 * umożliwiające pobranie wartosci wybranego pola z wybranego
 * wektora tablicy klasy, czy też jego modyfikację.
 * Ponadto umożliwia wykonanie mnożenia macierzy przez
 * wektor, wyliczenie wyznacznika, transpozycję macierzy oraz
 * podstawienie jednej macierzy do drugiej.
 */

/*!
 * \brief Klasa modeluje pojęcie macierzy kwadratowej
 * 
 * Klasa modeluje pojęcie macierzy jako jednowymiarowej tablicy 
 * wektorów o wielkości "Wymiar". Zawiera metody 
 * umożliwiające pobranie wartosci wybranego pola z wybranego
 * wektora tablicy klasy, czy też jego modyfikację.
 * Ponadto umożliwia wykonanie mnożenia macierzy przez
 * wektor, wyliczenie wyznacznika, transpozycję macierzy oraz
 * podstawienie jednej macierzy do drugiej.
 */

template <typename Typ, int Wymiar>
class SMacierz {
  SWektor<Typ,Wymiar> _Kolumna[Wymiar];
  /* Zapowiedzi definicji pomocniczych metod prywatnych*/
  void   Zamiana_kolumn_w_macierzy(unsigned int indeks1, unsigned int indeks2);
  int    Zamiana_z_elementem_niezerowym_i_zmiana_mnoznika(unsigned int indeks_kolumny);
  bool   Sprowadz_do_trojkatnej(int& mnoznik_wyznacznika);
  const Typ Wyznacznik_Oblicz();

  /* Zapowiedzi definicji metod publicznych*/
  public:
    const SWektor<Typ,Wymiar>& operator [] (unsigned int Kol) const {return _Kolumna[Kol];}
    SWektor<Typ,Wymiar>&       operator [] (unsigned int Kol) {return _Kolumna[Kol];}
    const Typ                  operator () (unsigned int Wie, unsigned int Kol) const {return _Kolumna[Kol][Wie];}
    Typ&                       operator () (unsigned int Wie, unsigned int Kol) {return _Kolumna[Kol][Wie];}
    SWektor<Typ,Wymiar>        operator *  (const SWektor<Typ,Wymiar>& Wek) const;
    const Typ     Wyznacznik() const;
    void          operator =  (const SMacierz<Typ,Wymiar>& Mac);
   
};

/*!
 * \brief Realizuje wyswietlenie elementow macierzy na strumien wyjsciowy.
 * 
 * Realizuje wyswietlenie elementow macierzy na strumien wyjsciowy.
 * \param[in] SrmWy - referencja do strumienia wyjsciowego - obiektu ostream
 * \param[in] Mac - referencja do stałej, wyswietlanej macierzy - obiektu klasy SMacierz
 * \retval Referencja do strumienia wyjsciowego
 */

template <typename Typ, int Wymiar>
std::ostream& operator << (std::ostream &StrmWy, const SMacierz<Typ,Wymiar> &Mac){
    for (unsigned int i=0; i < Wymiar; ++i){
        StrmWy << Mac[i];
        StrmWy << std::endl;
    }
    return StrmWy;
}

/*!
 * Wczytuje elementy macierzy na podstawie danych ze strumienia wejsciowego.
 * Argumenty:
 *    SrmWe - referencja do strumienia wejsciowego - obiektu istream
 *      Mac - referencja do wczytywanej macierzy - obiektu klasy SMacierz
 * Zwraca:
 *     Referencje do strumienia wejsciowego
 */

template <typename Typ, int Wymiar>
std::istream& operator >> (std::istream &StrmWe, SMacierz<Typ,Wymiar> &Mac){
    SWektor<Typ,Wymiar> wek; 
    for (unsigned int i=0; i < Wymiar; i++){ 
        StrmWe >> wek; /*Wczytanie wektora*/
        if (StrmWe.fail()){
        std::cerr << std::endl << "Blad wczytania jednego z wektorow macierzy!" << std::endl;    
        return StrmWe;
        }
        else{
        Mac[i] = wek; /*Przypisanie elementom kolumny elementów wektora*/
        }
    }
    return StrmWe;  
}

/*!
 * Przypisanie wartości elementów stalej macierzy argumentu do 
 * wartości elementów macierzy wywołania
 * Argumenty:
 *      Mac - referencja do stalej macierzy - obiektu klasy SMacierz
 *      Argument domyslny - modyfikowalny obiekt klasy SMacierz     
 */

template <typename Typ, int Wymiar>
void SMacierz<Typ,Wymiar>::operator= (const SMacierz<Typ,Wymiar>& Mac){
    for (unsigned int i=0; i < Wymiar; i++){
        _Kolumna[i] = Mac[i];
    }    
}

/*!
 * Mnozenie stalej macierzy wywolania przez staly wektor
 * wywolania
 * Argumenty:
 *      Wek - referencja do stalego wektora - klasy SWektor
 *      Argument domyslny - staly obiekt klasy SMacierz
 * Zwraca:
 *      wynik - wektor bedacy wynikiem operacji mnozenia   
 */

template <typename Typ, int Wymiar>
SWektor<Typ,Wymiar> SMacierz<Typ,Wymiar>::operator* (const SWektor<Typ,Wymiar>& Wek) const{
    SWektor<Typ,Wymiar> wynik;
    for (unsigned int i=0; i < Wymiar; i++){
        wynik[i] = (_Kolumna[i] * Wek);
    }
    return wynik;
}

/*!
 * Zamiana miejscami dwóch wybranych kolumn w macierzy wywołania
 * Argumenty:
 *      Argumenty domyślny - modyfikowalny obiekt klasy SMacierz
 *      indeks1, indeks2 - indeksy wybranych kolumn do zamiany  
 */
template <typename Typ, int Wymiar>
void SMacierz<Typ,Wymiar>::Zamiana_kolumn_w_macierzy(unsigned int indeks1, unsigned int indeks2){
    SWektor<Typ,Wymiar> pom;
    pom = _Kolumna[indeks1];
    _Kolumna[indeks1] = _Kolumna[indeks2];
    _Kolumna[indeks2] = pom;
}

/*!
 * Realizuje przegladanie wybranego wiersza macierzy w celu odnalezienia
 * kolumny z elementem niezerowym, a nastepnie zamiane kolumn.
 * Argumenty:
 *      Argumenty domyślny - modyfikowalny obiekt klasy SMacierz
 *      indeks_zera - okresla wiersz, ktory przeszukujemy oraz kolumne
 *                    poprzedzajaca ta, od ktorej zaczynamy przeszukiwanie
 * Zwraca:
 *      0 - nie udalo sie odnalezc elementu niezerowego
 *     -1 - udalo sie odnalezc element niezerowy - mnoznik wyznacznika
 *          zmienia znak na przeciwny    
 */
template <typename Typ, int Wymiar>
int SMacierz<Typ,Wymiar>::Zamiana_z_elementem_niezerowym_i_zmiana_mnoznika(unsigned int indeks_zera){
    unsigned int i;
    unsigned int j = indeks_zera;
    for(i = j+1; i<Wymiar; i++){
        if (_Kolumna[i][j] != 0){
            Zamiana_kolumn_w_macierzy(i,j);
            return (-1);
        }
    }
    return 0;
}

/*!
 * Realizuje sprowadzenie macierzy wywolania do macierzy trojkatnej
 * Argumenty:
 *      Argumenty domyślny - modyfikowalny obiekt klasy SMacierz
 *      mnoznik - referencja do obiektu int, ktory ulega zmianie
 *                w zaleznosci od ilosci wykonania operacji
 *                zamiany dwoch kolumn miejscami. Obiekt ten
 *                moze przyjac wartosc 1, -1 lub 0.
 * Zwraca:
 *      false - nie udalo sie sprowadzic do macierzy trojkatnej
 *      true  - udalo sie sprowadzic do macierzy trojkatnej   
 */
template <typename Typ, int Wymiar>
bool SMacierz<Typ,Wymiar>::Sprowadz_do_trojkatnej(int &mnoznik){
    unsigned int i;
    int j;
    for(j = 0; j<Wymiar; j++){
        if(_Kolumna[j][j] != 0){ /*Dla elementu niezerowego na przekatnej*/
            for(i = j+1; i<Wymiar; i++){
            /*Wyzerowanie kolumny*/    
            _Kolumna[i] = (_Kolumna[i] - (_Kolumna[j] * (_Kolumna[i][j] / _Kolumna[j][j])));    
            }
        }
        else{/*Element zerowy - koniecznosc znalezienia niezerowego*/
            mnoznik = mnoznik * Zamiana_z_elementem_niezerowym_i_zmiana_mnoznika(j);
            j -= 1; /* Petla wykona sie ponownie dla tego samego j*/
            if (mnoznik == 0){ /*Jesli nie udalo sie znalezc elem niezerowego*/
                return false;
            }
        }
    }
    return true;
}

/*!
 * Realizuje obliczenie wartosci wyznacznika macierzy wywolania
 * Argumenty:
 *      Argumenty domyślny - modyfikowalny obiekt klasy SMacierz
 * Zwraca:
 *      wartosc - wyliczona wartosc wynzacznika macierzy
 */

template <typename Typ, int Wymiar>
const Typ SMacierz<Typ,Wymiar>::Wyznacznik_Oblicz(){
    if (Wymiar == 1){ /*Jesli macierz zawiera tylko jeden element*/
        return _Kolumna[0][0];
    }
    else{
        Typ wartosc;
        wartosc = 1; /*Pomocnicza poczatkowa wartosc wyznacznika*/
        int mnoznik = 1; /* Mnoznik wyniku, zmienia sie w przypadku */
                         /* zamiany kolumn miejscami                */
        if (Sprowadz_do_trojkatnej(mnoznik) != false){
            for (unsigned int i = 0; i<Wymiar; ++i){
                wartosc = _Kolumna[i][i] * wartosc;
            }
        }
        else{
            wartosc = 0;
        }
    wartosc = wartosc * mnoznik;      
    return wartosc; 
    }
}

/*!
 * Podaje wartosc wyznacznika macierzy wywolania
 * Argumenty:
 *      Argumenty domyślny - staly obiekt klasy SMacierz
 * Zwraca:
 *      Wyliczona wartosc wyznacznika
 */
template <typename Typ, int Wymiar>
const Typ SMacierz<Typ,Wymiar>::Wyznacznik() const{
    SMacierz<Typ,Wymiar> Kopia = *this; /*Skopiowanie macierzy wywolania*/
    return Kopia.Wyznacznik_Oblicz();
}

#endif

