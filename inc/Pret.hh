#ifndef PRET_HH
#define PRET_HH

#include "typy_danych.hh"
#include "ObiektSceny.hh"

/*!
 * \file  
 * \brief Zawiera definicję klasy Pret
 *
 *  Plik zawiera definicję klasy Pret, sluzacej do
 *  interpretacji zadanego obiektu jako preta majacego
 *  okreslone wspolrzedne w ukladzie kartezjanskim. 
 */

/*!
 * \brief Pret jako obiekt graficzny
 *
 *  Klasa umożliwia interpretowanie obiektu jako preta
 *  o okreslonych wspolrzednych w ukladzie kartezjanskim.
 */
class Pret: public ObiektSceny
{
    public:
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
    bool WyznaczWsp() override;
};

#endif