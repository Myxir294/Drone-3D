#ifndef POWIERZCHNIAFALOWANA_HH
#define POWIERZCHNIAFALOWANA_HH

#include "typy_danych.hh"
#include "ObiektSceny.hh"
/*!
 * \file  
 * \brief Zawiera definicję klasy PowierzchniaFalowana
 *
 *  Plik zawiera definicję klasy PowierzchniaFalowana, sluzacej do
 *  interpretacji zadanego obiektu jako powierzchni falowanej majacej
 *  okreslone wspolrzedne w ukladzie kartezjanskim. 
 */

/*!
 * \brief PowierzchniaFalowana jako obiekt graficzny
 *
 *  Klasa umożliwia interpretowanie obiektu jako powierzchni falowanej
 *  o okreslonych wspolrzednych w ukladzie kartezjanskim.
 */
class PowierzchniaFalowana: public ObiektSceny
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