#ifndef SWEKTOR_HH
#define SWEKTOR_HH

#include <iostream>
#include <cmath>

/*!
 * \file
 * \brief Plik zawiera szablon klasy modelujacej pojecie wektora
 *  
 * Plik zawiera szablon klasy modelujacej pojęcie wektora jako 
 * jednowymiarowej tablicy elementów double, o rozmiarze ROZMIAR. 
 * Zawiera ona metody umożliwiające pobranie wartosci wybranego 
 * pola tablicy klasy, czy też jego modyfikację.
 * Ponadto umożliwia wykonywanie działań arytmetycznych na 
 * wektorach, mnożenie i dzielenie wektora przez liczbę typu
 * double, podanie długości wektora oraz przypisanie jednego
 * wektora do drugiego.
 */

/*!
 * \brief Klasa modeluje pojecie wektora
 *  
 * Klasa modeluje pojęcie wektora jako jednowymiarowej tablicy 
 * elementów double, o rozmiarze ROZMIAR. Zawiera metody 
 * umożliwiające pobranie wartosci wybranego pola tablicy 
 * klasy, czy też jego modyfikację.
 * Ponadto umożliwia wykonywanie działań arytmetycznych na 
 * wektorach, mnożenie i dzielenie wektora przez liczbę typu
 * double, podanie długości wektora oraz przypisanie jednego
 * wektora do drugiego.
 */

template <typename Typ, int Wymiar>
class SWektor{
    Typ _Wsp[Wymiar];
 /*Zapowiedzi definicji metod publicznych*/
 public:
    SWektor() {for (Typ &Wsp: _Wsp) Wsp = 0;}
    const Typ           operator []  (unsigned int indeks) const  {return _Wsp[indeks];}
    Typ&                operator []  (unsigned int indeks)        {return _Wsp[indeks];}
    SWektor<Typ,Wymiar> operator - (const SWektor<Typ,Wymiar> &wek) const;
    SWektor<Typ,Wymiar> operator + (const SWektor<Typ,Wymiar> &wek) const;
    Typ                 operator * (const SWektor<Typ,Wymiar> &wek) const;
    SWektor<Typ,Wymiar> operator * (Typ liczba) const;
    SWektor<Typ,Wymiar> operator / (Typ liczba) const;
    void                operator = (const SWektor<Typ,Wymiar> &wek);
};

/*!
 * Realizuje wyswietlenie elementow wektora na strumien wyjsciowy.
 * Argumenty:
 *    SrmWe - referencja do strumienia wejsciowego - obiektu istream
 *      Wek - referencja do stałego, wyswietlanego wektora - obiektu klasy SWektor
 * Zwraca:
 *     Referencje do strumienia wejsciowego
 */
template<typename Typ, int Wymiar>
std::ostream& operator << (std::ostream &StrmWy, const SWektor<Typ,Wymiar> &Wek){
    for (unsigned int i = 0; i < Wymiar; ++i){
        StrmWy << Wek[i] << " ";
    }
    return StrmWy;
}

/*!
 * Wczytuje elementy wektora na podstawie danych ze strumienia wejsciowego.
 * Argumenty:
 *    SrmWe - referencja do strumienia wejsciowego - obiektu istream
 *      Wek - referencja do wczytywanego wektora - obiektu klasy SWektor
 * Zwraca:
 *     Referencje do strumienia wejsciowego
 */
template<typename Typ, int Wymiar>
std::istream& operator >> (std::istream &StrmWe, SWektor<Typ,Wymiar> &Wek){
    Typ elem;
    for (unsigned int i = 0; i < Wymiar; ++i){
        StrmWe >> elem;
        if (StrmWe.fail()){
            std::cerr << std::endl << "Napotkano bledna wartosc pola wektora" << std::endl;
            return StrmWe;
        }
        else{
            Wek[i] = elem; /*Przypisanie elementowi wektora wczytanej wartosci*/
        }
    }
    return StrmWe;
}  

/*!
 * Wykonanie operacji odejmowania wektorów
 * Argumenty:
 *      Argument domyslny - staly obiekt klasy SWektor
 *                     w2 - referencja do stałego obiektu klasy SWektor
 * Zwraca:
 *      pom - wektor bedacy różnicą dwóch wektorów wywołania     
 */

template <typename Typ, int Wymiar>
SWektor<Typ,Wymiar> SWektor<Typ,Wymiar>::operator - (const SWektor<Typ,Wymiar> &w2) const
{
  SWektor<Typ,Wymiar>  Wynik;
    for (unsigned int i = 0; i < Wymiar; ++i){
        Wynik[i] = ((*this)[i] - w2[i]);
    }
    return Wynik;
}

/*!
 * Wykonanie operacji dodawania wektorów
 * Argumenty:
 *      Argument domyslny - staly obiekt klasy SWektor
 *                     w2 - referencja do stałego obiektu klasy SWektor
 * Zwraca:
 *      pom - wektor bedacy sumą dwóch wektorów wywołania     
 */
template <typename Typ, int Wymiar>
SWektor<Typ,Wymiar> SWektor<Typ,Wymiar>::operator + (const SWektor<Typ,Wymiar> &w2) const
{
  SWektor<Typ,Wymiar>  Wynik;
    for (unsigned int i = 0; i < Wymiar; ++i){
        Wynik[i] = ((*this)[i] + w2[i]);
    }
    return Wynik;
}

/*!
 * Wykonanie operacji mnożenia wektorów skalaranie
 * Argumenty:
 *      Argument domyslny - staly obiekt klasy SWektor
 *                     w2 - referencja do stałego obiektu klasy SWektor
 * Zwraca:
 *      wynik - iloczyn skalarny wektorów wywołania     
 */
template <typename Typ, int Wymiar>
Typ SWektor<Typ,Wymiar>::operator * (const SWektor<Typ,Wymiar> &w2) const
{
    Typ wynik;
    wynik = 0;
    for (unsigned int i = 0; i < Wymiar; i++){
        wynik = wynik + ((*this)[i] * w2[i]);
    }
    return wynik;
}

/*!
 * Wykonanie operacji mnożenia wektora przez liczbę typu Typ
 * Argumenty:
 *      Argument domyslny - staly obiekt klasy SWektor
 *                 liczba - referencja do stałego obiektu typu Typ
 * Zwraca:
 *      wynik - wektor bedacy wynikiem operacji     
 */
template <typename Typ, int Wymiar>
SWektor<Typ,Wymiar> SWektor<Typ,Wymiar>::operator * (Typ liczba) const
{
  SWektor<Typ,Wymiar>  Wynik;

    for (unsigned int i = 0; i < Wymiar; ++i){
        Wynik[i] = ((*this)[i] * liczba);
    }
    return Wynik;  
}

/*!
 * Wykonanie operacji dzielenia wektora przez liczbę typu Typ
 * Argumenty:
 *      Argument domyslny - staly obiekt klasy SWektor
 *                 liczba - referencja do stałego obiektu typu Typ
 * Zwraca:
 *      wynik - wektor bedacy wynikiem operacji     
 */
template <typename Typ, int Wymiar>
SWektor<Typ,Wymiar> SWektor<Typ,Wymiar>::operator / (Typ liczba) const
{
  SWektor<Typ,Wymiar>  Wynik;

    for (unsigned int i = 0; i < Wymiar; ++i){
        Wynik[i] = ((*this)[i] / liczba);
    }
    return Wynik;  
}

/*!
 * Wykonanie operacji podstawienia wartości elementów jednego
 * wektora do elemenetów drugiego wektora.
 * Argumenty:
 *      Argument domyslny - modyfikowalny obiekt klasy SWektor
 *                     w2 - referencja do stałego obiektu typu SWektor   
 */
template <typename Typ, int Wymiar>
void SWektor<Typ,Wymiar>::operator = (const SWektor<Typ,Wymiar> &w2){
    for (unsigned int i = 0; i < Wymiar; i++){
        (*this)[i] = w2[i];
    }
}
 
#endif