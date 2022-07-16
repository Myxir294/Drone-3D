#include "ProstopadloscianSCN.hh"

using namespace std;

/*!
 * \file  
 * \brief Zawiera definicje dluzszych metod klasy \link ProstopadloscianSCN \endlink
 *
 *  Zawiera definicje dluzszych metod klasy \link ProstopadloscianSCN \endlink
 *
 */

bool ProstopadloscianSCN::ObliczGlobalne() const
{
    ifstream StrmWej(PodajNazwePlikuLok());
    ofstream StrmWyj(PodajNazwePlikuGlob());

    if (!StrmWej.is_open() || !StrmWyj.is_open()) {return false;}

    Macierz3x3 Mac_Obrotu_OZ; /* Macierz obrotu uzywana w celu odpowiedniego */ 
                              /* przeksztalcenia wspolrzednych               */
    double kat_rad = _Kat_Orientacji * (M_PI / 180);
    Mac_Obrotu_OZ(0,0) = cos(kat_rad);
    Mac_Obrotu_OZ(0,1) = sin(kat_rad);
    Mac_Obrotu_OZ(1,0) = -sin(kat_rad);
    Mac_Obrotu_OZ(1,1) = cos(kat_rad);
    Mac_Obrotu_OZ(2,2) = 1; 

    Wektor3D pom;
    unsigned int j = 0;

    for(unsigned int i = 0; i < 20; ++i)
    {
        StrmWej >> pom;
        if(StrmWej.fail()){return false;}
        StrmWyj << (Mac_Obrotu_OZ * pom) + _Wek_Translacji << endl; /*Zapis nowych wspolrzednych*/
        if(StrmWyj.fail()){return false;}
        
        ++j;
        if (j == 4)
        {
            StrmWej.ignore(1000,'#');
            StrmWyj << '#' << endl << endl;
            if(StrmWyj.fail()){return false;}
            j = 0;
        }
    }  
    StrmWej.close();
    StrmWyj.close();
    return true;
}
bool ProstopadloscianSCN::WyznaczWsp()
{
    std::ifstream Strm(PodajNazwePlikuGlob()); /*Odczyt danych z pliku*/
    if (!Strm.is_open()) {return false;}
    unsigned int k = 0;
    Wektor3D pom;

    for (unsigned int i = 0; i < 20; ++i)
    {   
        if(k == 4)
        {
            Strm.ignore(1000,'#');
            k = 0;
        }
        Strm >> pom;
        if (Strm.fail()) /*Srawdzenie poprawnosci danych*/
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

bool ProstopadloscianSCN::WybierzPliki(const char *NazwaPlikuWe, const char *NazwaPlikuWy){
    WybierzPlikLok(NazwaPlikuWe);
    WybierzPlikGlob(NazwaPlikuWy);
    Wyznacz_Promien_i_Srodek();   
    return ObliczGlobalne();
}

void ProstopadloscianSCN::Zmien_o_kat(int kat)
{
    _Kat_Orientacji += kat;
    if (_Kat_Orientacji == 360 || _Kat_Orientacji == -360)
    {
        _Kat_Orientacji = 0;
    }
}

