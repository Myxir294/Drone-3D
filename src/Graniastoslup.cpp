#include "Graniastoslup.hh"

/*!
 * \file  
 * \brief Zawiera definicje dluzszych metod klasy \link Graniastoslup \endlink
 *
 *  Zawiera definicje dluzszych metod klasy \link Graniastoslup \endlink
 *
 */

void Graniastoslup::Wyznacz_Promien_i_Srodek()
{   

    std::ifstream Strm(PodajNazwePlikuLok()); /*Odczyt danych z pliku*/
    Wektor3D pom;
    unsigned int k = 0;
    for (unsigned int i = 0; i < 28; ++i)
    {
        Strm >> pom;
        if (i == 0)
        {
            PodajWspMax() = pom;
            PodajWspMin() = pom;
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
        ++k;
        if (k == 4)
        {
           Strm.ignore(1000,'#');
           k = 0; 
        }
    }
    _srodek_lok = (PodajWspMax() + PodajWspMin()) / 2;
    _promien = sqrt((pom - _srodek_lok) * (pom - _srodek_lok));

    Strm.close();

}
bool Graniastoslup::WyznaczWsp()
{
    std::ifstream Strm(PodajNazwePlikuLok()); /*Odczyt danych z pliku*/
    if (!Strm.is_open()) {return false;}
    unsigned int k = 0;
    Wektor3D pom;

    for (unsigned int i = 0; i < 28; ++i)
    {   
        if(k == 4)
        {
            Strm.ignore(1000,'#');
            k = 0;
        }
        Strm >> pom;
        if (Strm.fail()) /*Sprawdzenie poprawnosci danych*/
        {
            return false;
        }

        if(i == 0)
        {
            PodajWspMin() = pom;
            PodajWspMax() = pom;
        }
        else
        {
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
        ++k; 
    }
    return true;
} 
