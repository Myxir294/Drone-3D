#ifndef TYPY_DANYCH_HH
#define TYPY_DANYCH_HH
#include "SMacierz.hh"

#define DOKLADNOSC_KATA_ODSWIEZANIA 5
#define DOKLADNOSC_WEKTORA_ODSWIEZANIA 5
#define CZAS_ODSWIEZANIA 100000

/*!
 * \file  
 * \brief Zawiera definicję Wektora3D oraz Macierzy3x3
 *
 *  Plik zawiera definicję Wektora3D jako obiektu
 *  SWektor o rozmiarze 3 z polami typu double oraz
 *  definicję Macierzy3x3 jako obiektu SMacierz
 *  o rozmiarze 3, składającego sie z wektorów o 
 *  polach typu double.  
 */

typedef SWektor<double,3> Wektor3D;
typedef SMacierz<double,3> Macierz3x3;

#endif