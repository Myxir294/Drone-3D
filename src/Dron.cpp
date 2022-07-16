#include "Dron.hh"

/*!
 * \file  
 * \brief Zawiera definicje dluzszych metod klasy \link Dron \endlink
 *
 *  Zawiera definicje dluzszych metod klasy \link Dron \endlink
 *
 */
bool Dron::SprawdzMozliwoscRuchuSruby(ObiektSceny &obiekt, GraniastoslupSCN &sruba)
{   
    Wektor3D MaxSruby;
    Wektor3D MinSruby;
    Wektor3D MaxObiektu;
    Wektor3D MinObiektu;
    bool sukces;
    std::string Nazwa; 
    Nazwa = sruba.PodajNazwePlikuGlob(); /*Pobranie obecnej nazwy pliku wyjsciowego*/
    char* PoprzedniaNazwa = &Nazwa[0]; 
    sruba.WybierzPlikGlob("bryly/temp.dat"); /* Wybor nowego, tymczasowego pliku dla danych wyjsciowych*/
    sukces = sruba.ObliczGlobalne();
    if(!sukces) {return false;}
    sukces = sruba.WyznaczWsp(); /*Okreslenie wspolrzednych skrajnych sruby*/
    if(!sukces) {return false;}
    MaxSruby = sruba.PodajWspMax();
    MinSruby = sruba.PodajWspMin();
    MaxObiektu = obiekt.PodajWspMax();
    MinObiektu = obiekt.PodajWspMin();

    /*Jezeli zachodzi ktorekolwiek z ponizszych, to ruch jest mozliwy*/
    if(MaxSruby[0] > MaxObiektu[0] && MinSruby[0] > MaxObiektu[0])
    {  
        sruba.WybierzPlikGlob(PoprzedniaNazwa); /*Przywrocenie poprzedniej nazwy pliku*/
        return true;
    }
    if(MaxSruby[1] > MaxObiektu[1] && MinSruby[1] > MaxObiektu[1])
    {     
        sruba.WybierzPlikGlob(PoprzedniaNazwa);
        return true;
    }
    if(MaxSruby[2] > MaxObiektu[2] && MinSruby[2] > MaxObiektu[2])
    {   
        sruba.WybierzPlikGlob(PoprzedniaNazwa);
        return true;
    } 
    if(MaxSruby[0] < MinObiektu[0] && MinSruby[0] < MinObiektu[0])
    {
        sruba.WybierzPlikGlob(PoprzedniaNazwa);
        return true;
    }
    if(MaxSruby[1] < MinObiektu[1] && MinSruby[1] < MinObiektu[1])
    {
        sruba.WybierzPlikGlob(PoprzedniaNazwa);
        return true;
    }
    if(MaxSruby[2] < MinObiektu[2] && MinSruby[2] < MinObiektu[2])
    {
        sruba.WybierzPlikGlob(PoprzedniaNazwa);
        return true;
    }
    /*Nic z powyzszych nie zaszlo, zatem ruch spowoduje kolizje*/
    sruba.WybierzPlikGlob(PoprzedniaNazwa);
    return false;                      
} 

bool Dron::SprawdzMozliwoscRuchuRdzenia(ObiektSceny &obiekt)
{   
    /*Wszystko wykonuje sie analogicznie jak podczas sprawdzania kolizyjnosci sruby*/
    Wektor3D MaxRdzenia;
    Wektor3D MinRdzenia;
    Wektor3D MaxObiektu;
    Wektor3D MinObiektu;
    bool sukces;
    std::string Nazwa = Wez_Rdzen().PodajNazwePlikuGlob();
    Wez_Rdzen().WybierzPlikGlob("bryly/temp.dat");
    char* PoprzedniaNazwa = &Nazwa[0];
    sukces = Wez_Rdzen().ObliczGlobalne();
    if(!sukces) {return false;}
    sukces = Wez_Rdzen().WyznaczWsp();
    if(!sukces) {return false;}
    MaxRdzenia = Wez_Rdzen().PodajWspMax();
    MinRdzenia = Wez_Rdzen().PodajWspMin();
    MaxObiektu = obiekt.PodajWspMax();
    MinObiektu = obiekt.PodajWspMin();
    if (MaxRdzenia[0] > MaxObiektu[0] && MinRdzenia[0] > MaxObiektu[0])
    {
        Wez_Rdzen().WybierzPlikGlob(PoprzedniaNazwa);
        return true;
    }
    if(MaxRdzenia[1] > MaxObiektu[1] && MinRdzenia[1] > MaxObiektu[1])
    {

        Wez_Rdzen().WybierzPlikGlob(PoprzedniaNazwa);
        return true;
    }
    if(MaxRdzenia[2] > MaxObiektu[2] && MinRdzenia[2] > MaxObiektu[2])
    {

        Wez_Rdzen().WybierzPlikGlob(PoprzedniaNazwa);
        return true;
    } 
    if(MaxRdzenia[0] < MinObiektu[0] && MinRdzenia[0] < MinObiektu[0])
    {

        Wez_Rdzen().WybierzPlikGlob(PoprzedniaNazwa);
        return true;
    }
    if(MaxRdzenia[1] < MinObiektu[1] && MinRdzenia[1] < MinObiektu[1])
    {

        Wez_Rdzen().WybierzPlikGlob(PoprzedniaNazwa);
        return true;
    }
    if(MaxRdzenia[2] < MinObiektu[2] && MinRdzenia[2] < MinObiektu[2])
    {

        Wez_Rdzen().WybierzPlikGlob(PoprzedniaNazwa);
        return true;
    }
    Wez_Rdzen().WybierzPlikGlob(PoprzedniaNazwa);
    return false;                      
}

bool Dron::SprawdzMozliwoscRuchu(ObiektSceny &obiekt)
{   
    /*Sprawdzenie po kolei kolizyjnosci kazdego z elementow skladowych*/
    bool sukces;
    sukces = SprawdzMozliwoscRuchuSruby(obiekt, _LewaSruba); 
    if(!sukces) {return false;}
    sukces = SprawdzMozliwoscRuchuSruby(obiekt, _PrawaSruba);
    if(!sukces) {return false;}
    sukces = SprawdzMozliwoscRuchuRdzenia(obiekt);
    return sukces;
}

void Dron::Zmien_o_kat(unsigned int kat) 
{   
    /*Zmiana kata po kolei dla kazdego elementu skladowego*/
    _Rdzen.Zmien_o_kat(kat);
    _LewaSruba.Zmien_o_kat(kat);
    _PrawaSruba.Zmien_o_kat(kat);
}
void Dron::Zmien_o_kat_wlasny(unsigned int kat)
{   
    /*Obrot obydwu srob*/
    _LewaSruba.Zmien_o_kat_wlasny(kat);
    _PrawaSruba.Zmien_o_kat_wlasny(kat);
}
void Dron::Zmien_o_translacje(Wektor3D Translacja)
{   
    /*Zmiana polozenia po kolei dla kazdego elementu skladowego*/
    _Rdzen.Zmien_o_translacje(Translacja);
    _LewaSruba.Zmien_o_translacje(Translacja);
    _PrawaSruba.Zmien_o_translacje(Translacja);
}

bool Dron::ObliczGlobalne() const
{   
    /*Obliczenie wspolrzednych globalnych po kolei dla kazdego elementu skladowego*/
    bool sukces;
    sukces = _Rdzen.ObliczGlobalne();
    if(!sukces) {return false;}
    sukces = _LewaSruba.ObliczGlobalne();
    if(!sukces) {return false;}
    sukces = _PrawaSruba.ObliczGlobalne();
    return true;
}