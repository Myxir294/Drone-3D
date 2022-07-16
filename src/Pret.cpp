#include "Pret.hh"

/*!
 * \file  
 * \brief Zawiera definicje dluzszych metod klasy \link Pret \endlink
 *
 *  Zawiera definicje dluzszych metod klasy \link Pret \endlink
 *
 */

bool Pret::WyznaczWsp()
{
    std::ifstream Strm(PodajNazwePlikuLok()); /*Odczyt danych z pliku*/
    if (!Strm.is_open()) {return false;}
    Wektor3D pom;

    Strm >> pom;
    if (Strm.fail()) /*Srawdzenie poprawnosci danych*/
    {
        return false;
    }
    PodajWspMin() = pom;
    PodajWspMax() = pom;
    Strm >> pom;
    if (Strm.fail()) /*Srawdzenie poprawnosci danych*/
    {
        return false;
    }

    for (unsigned int j = 0; j < 3; ++j)
    {
        if (pom[j] > PodajWspMax()[j])
        {
            PodajWspMax()[j] = pom[j];
        }
        if (pom[j] < PodajWspMin()[j])
        {
            PodajWspMin()[j] = pom[j];
        }
    }
    Strm.close();
    return true;
}  
