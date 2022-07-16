#include "PowierzchniaFalowana.hh"

/*!
 * \file  
 * \brief Zawiera definicje dluzszych metod klasy \link PowierzchniaFalowana \endlink
 *
 *  Zawiera definicje dluzszych metod klasy \link PowierzchniaFalowana \endlink
 *
 */

bool PowierzchniaFalowana::WyznaczWsp()
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
    for (unsigned int i = 0; i < 41; ++i)
    {
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
    }
    Strm.close();
    return true;
}
