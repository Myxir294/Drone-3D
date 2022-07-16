#include "GraniastoslupSCN.hh"

using namespace std;

/*!
 * \file  
 * \brief Zawiera definicje dluzszych metod klasy \link GraniastoslupSCN \endlink
 *
 *  Zawiera definicje dluzszych metod klasy \link GraniastoslupSCN \endlink
 *
 */

GraniastoslupSCN::GraniastoslupSCN()
{ 
    _Kat_Orientacji_OZ = 0; 
    _Kat_Orientacji_OX = 0;
}

bool GraniastoslupSCN::WyznaczWsp()
{
    ifstream Strm(PodajNazwePlikuGlob()); /*Odczyt danych z pliku*/
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

bool GraniastoslupSCN::ObliczGlobalne() const
{
    ifstream StrmWej(PodajNazwePlikuLok());
    ofstream StrmWyj(PodajNazwePlikuGlob());

    if (!StrmWej.is_open() || !StrmWyj.is_open()) {return false;}

    Macierz3x3 Mac_Obrotu_OZ; /* Macierz obrotu uzywana w celu odpowiedniego */ 
                              /* przeksztalcenia wspolrzednych               */
    double kat_rad = _Kat_Orientacji_OZ * (M_PI / 180);
    Mac_Obrotu_OZ(0,0) = cos(kat_rad);
    Mac_Obrotu_OZ(0,1) = sin(kat_rad);
    Mac_Obrotu_OZ(1,0) = -sin(kat_rad);
    Mac_Obrotu_OZ(1,1) = cos(kat_rad);
    Mac_Obrotu_OZ(2,2) = 1;

    Macierz3x3 Mac_Obrotu_OX;

    double kat_rad2 = _Kat_Orientacji_OX * (M_PI / 180);
    Mac_Obrotu_OX(0,0) = 1;
    Mac_Obrotu_OX(1,1) = cos(kat_rad2);
    Mac_Obrotu_OX(2,1) = -sin(kat_rad2);
    Mac_Obrotu_OX(1,2) = sin(kat_rad2);
    Mac_Obrotu_OX(2,2) = cos(kat_rad2);
    

    Wektor3D pom;
    Wektor3D pom2;
    Wektor3D pom3;
    unsigned int j = 0;

    for(unsigned int i = 0; i < 28; ++i)
    {
        StrmWej >> pom2;
        if(StrmWej.fail()){return false;}

        pom3 = (Mac_Obrotu_OX * (pom2 - PodajSrodekLok()));
        pom = pom3 + PodajSrodekLok();

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

bool GraniastoslupSCN::WybierzPliki(const char *NazwaPlikuWe, const char *NazwaPlikuWy, const unsigned int numer){
    WybierzPlikLok(NazwaPlikuWe);
    WybierzPlikGlob(NazwaPlikuWy);
    Wyznacz_Promien_i_Srodek();
    return ObliczGlobalne();
}


void GraniastoslupSCN::Zmien_o_kat(int kat)
{
    _Kat_Orientacji_OZ += kat;
    if (_Kat_Orientacji_OZ == 360 || _Kat_Orientacji_OZ == -360)
    {
        _Kat_Orientacji_OZ = 0;
    }
}

void GraniastoslupSCN::Zmien_o_kat_wlasny(int kat)
{
    _Kat_Orientacji_OX += kat;
    if (_Kat_Orientacji_OX == 360 || _Kat_Orientacji_OX == -360)
    {
        _Kat_Orientacji_OX = 0;
    }
}

