#include "Scena.hh"
#include "Dron.hh"

/*!
 * \file  
 * \brief Zawiera definicje dluzszych metod klasy \link Scena \endlink
 *
 *  Zawiera definicje dluzszych metod klasy \link Scena \endlink
 *
 */

Wektor3D Scena::ObliczWektorPrzesuniecia(unsigned int dlugosc, int kat_z, int kat_orientacji) const
{
    Wektor3D pom;
    pom[0] = (dlugosc * cos(kat_orientacji * (M_PI / 180)));
    pom[1] = (dlugosc * sin(kat_orientacji * (M_PI / 180)));
    if (kat_z > -90 && kat_z < 90 && kat_z != 0) /*Sprawdzenie poprawnosci kata*/
    { 
      if (kat_z < 0) /*Zanurzanie*/
      {
        pom[2] = (0 - (dlugosc / cos(kat_z * (M_PI / 180))));
      }
      else /*Wynurzanie*/
      {
        pom[2] = (dlugosc / cos(kat_z * (M_PI / 180)));
      }
    }
    return pom;
}


bool Scena::Dodaj_Powierzchnie(const char *NazwaPliku)
{
  bool sukces;
  Lista.push_back(new Powierzchnia()); /*Utworzenie obiektu dynamicznie z wykorzystanie rzutowania w gore*/
  Lista.back()->WybierzPlikLok(NazwaPliku);
  sukces = Lista.back()->WyznaczWsp();
  if (!sukces) {return false;}
  sukces = Lacze.DodajNazwePliku(NazwaPliku);
  if (!sukces) {return false;}
  return true;
}

bool Scena::Dodaj_Powierzchnie_Falowana(const char *NazwaPliku)
{
  bool sukces;
  Woda.WybierzPlikLok(NazwaPliku);
  sukces = Woda.WyznaczWsp();
  if (!sukces) {return false;}
  sukces = Lacze.DodajNazwePliku(NazwaPliku);
  if (!sukces) {return false;}
  return true;
}

bool Scena::Dodaj_Bryle(const char *NazwaPliku)
{
  bool sukces;
  Lista.push_back(new Prostopadloscian()); /*Utworzenie obiektu dynamicznie z wykorzystanie rzutowania w gore*/
  Lista.back()->WybierzPlikLok(NazwaPliku);
  sukces = Lista.back()->WyznaczWsp();
  if (!sukces) {return false;}
  sukces = Lacze.DodajNazwePliku(NazwaPliku);
  if (!sukces) {return false;}
  return true;
}

bool Scena::Dodaj_Pret(const char *NazwaPliku)
{
  bool sukces;
  Lista.push_back(new Pret());
  Lista.back()->WybierzPlikLok(NazwaPliku); /*Utworzenie obiektu dynamicznie z wykorzystanie rzutowania w gore*/
  sukces = Lista.back()->WyznaczWsp();
  if (!sukces) {return false;}
  sukces = Lacze.DodajNazwePliku(NazwaPliku);
  if (!sukces) {return false;}
  return true;
}

bool Scena::Dodaj_Drona(Dron &Element, 
                        const char *NazwaPlikuWeRdzen,
                        const char *NazwaPlikuWeLSruba,
                        const char *NazwaPlikuWePSruba, 
                        const char *NazwaPlikuWyRdzen,
                        const char *NazwaPlikuWyLSruba,
                        const char *NazwaPlikuWyPSruba
                      )
{   
  bool sukces;
  sukces = Element.Wez_Rdzen().WybierzPliki(NazwaPlikuWeRdzen, NazwaPlikuWyRdzen);
  if (!sukces) {return false;}
  sukces = Element.Wez_Lewa_Srube().WybierzPliki(NazwaPlikuWeLSruba, NazwaPlikuWyLSruba, 1);
  if (!sukces) {return false;}
  sukces = Element.Wez_Prawa_Srube().WybierzPliki(NazwaPlikuWePSruba, NazwaPlikuWyPSruba, 2);
  if (!sukces) {return false;}
  sukces = Lacze.DodajNazwePliku(NazwaPlikuWyRdzen);
  if (!sukces) {return false;}
  sukces = Lacze.DodajNazwePliku(NazwaPlikuWyLSruba);
  if (!sukces) {return false;}
  sukces = Lacze.DodajNazwePliku(NazwaPlikuWyPSruba);
  if (!sukces) {return false;}
  return true;
}

bool Scena::InicjalizujScene()
{ 
  bool sukces;
  sukces = Dodaj_Powierzchnie_Falowana("bryly/woda.dat");
  if (!sukces) {return false;}  
  sukces = Dodaj_Powierzchnie("bryly/powierzchnia.dat");
  if (!sukces) {return false;}
  sukces = Dodaj_Powierzchnie("bryly/sciana.dat");
  if (!sukces) {return false;}  
  sukces = Dodaj_Bryle("bryly/prostopadloscian.dat");
  if (!sukces) {return false;}
  sukces = Dodaj_Pret("bryly/pret.dat");
  if (!sukces) {return false;}     
  sukces = Dodaj_Drona( Wez_Drona1(),
                       "bryly/rdzendrona.dat",
                       "bryly/lewasruba1.dat",
                       "bryly/prawasruba1.dat",
                       "bryly/rdzendrona2.dat",
                       "bryly/lewasruba2.dat",
                       "bryly/prawasruba2.dat"
                       );
  if (!sukces) {return false;}
  Lacze.ZmienTrybRys(PzG::TR_3D);
  Lacze.Inicjalizuj();
  Lacze.UstawZakresX(-100, 100);
  Lacze.UstawZakresY(-100, 100);
  Lacze.UstawZakresZ(0, 300);
  Lacze.UstawRotacjeXZ(72,345); 
  Rysuj_Scene();
  
  
  return true;
}

bool Scena::Animowany_Obrot_Bryly(Dron &Element, int kat_obrotu)
{   
  int kat_bezwzgl = fabs(kat_obrotu);
  int dokladnosc_pom;
  if(kat_obrotu < 0) /*Obrot przeciwnie do ruchu wskazowek zegara*/
  {
    dokladnosc_pom = 0 - DOKLADNOSC_KATA_ODSWIEZANIA;
  }
  else /*Obrot zgonie z ruchem wskazowek zegara*/
  {
    dokladnosc_pom = DOKLADNOSC_KATA_ODSWIEZANIA;
  }
  
  if (kat_bezwzgl >= DOKLADNOSC_KATA_ODSWIEZANIA) /*Okreslenie, czy obrot jest zauwazalny*/
  { 
    /*Podzial obrotu na fazy w celu uzyskania efektu animacji*/
    for(int i = 0; i <= (kat_bezwzgl - DOKLADNOSC_KATA_ODSWIEZANIA); i += DOKLADNOSC_KATA_ODSWIEZANIA)
    {   
        Element.Zmien_o_kat_wlasny(dokladnosc_pom);
        Element.Zmien_o_kat(dokladnosc_pom); /*Faza obrotu*/
        
        for (ObiektSceny* ptr: Lista) /* Sprawdzenie kolizyjnosci dla kazdej przeszkody*/
        {
          if(!Element.SprawdzMozliwoscRuchu(*ptr))
          {
            std::cout << "Wykryto kolizje" << std::endl;
            dokladnosc_pom = 0 - dokladnosc_pom;
            Element.Zmien_o_kat_wlasny(dokladnosc_pom); /*Cofniecie drona*/
            Element.Zmien_o_kat(dokladnosc_pom); 
            return false;             
          }        
        }        
    
        if(!Element.ObliczGlobalne()){return false;}
        Rysuj_Scene();
        usleep(CZAS_ODSWIEZANIA);  
    }
  }
  return true;
}


bool Scena::SprawdzWynurzenie(Dron &Element) const 
{ 
  return (Element.Wez_Rdzen().PodajWspMin()[2] >= Woda.PodajWspMin()[2]);
}

bool Scena::Animowana_Translacja_Bryly(Dron &Element, int kat_z, unsigned int dlugosc)
{
  if (dlugosc >= DOKLADNOSC_WEKTORA_ODSWIEZANIA) /* Okreslenie, czy ruch jest zauwazalny*/
  {
    Wektor3D pom;
    Wektor3D pom2;    
    /*Podzial ruchu na fazy w celu uzyskania efektu animacji*/
    for(unsigned int i = 0; i <= (dlugosc - DOKLADNOSC_WEKTORA_ODSWIEZANIA); i += DOKLADNOSC_WEKTORA_ODSWIEZANIA)
    { 
      pom = ObliczWektorPrzesuniecia(DOKLADNOSC_WEKTORA_ODSWIEZANIA, kat_z, Element.Wez_Rdzen().PodajKatOrientacji());
      { 
        Element.Zmien_o_kat_wlasny(DOKLADNOSC_KATA_ODSWIEZANIA);
        Element.Zmien_o_translacje(pom); /*Faza ruchu*/
       
        for (ObiektSceny* ptr: Lista) /* Sprawdzenie kolizyjnosci dla kazdej przeszkody*/
        {
          if(!Element.SprawdzMozliwoscRuchu(*ptr))
          {
            std::cout << "Wykryto kolizje" << std::endl;
            pom = pom2 - pom;
            Element.Zmien_o_translacje(pom); /*Cofniecie drona*/          
            return false;           
          }        
        }                  

        if(SprawdzWynurzenie(Element)) /*Sprawdzenie stopnia wynurzenia*/
        {
          pom = pom2 - pom;
          Element.Zmien_o_translacje(pom); /*Cofniecie drona*/             
          kat_z = 0; /*Zignorowanie dalszych zadanych zmian wysokosci*/
          pom = ObliczWektorPrzesuniecia(DOKLADNOSC_WEKTORA_ODSWIEZANIA, kat_z, Element.Wez_Rdzen().PodajKatOrientacji());
          Element.Zmien_o_translacje(pom); /*Ponowny ruch*/
        }                 
        if(!Element.ObliczGlobalne())
        {
          return false;
        }
        Rysuj_Scene();
        usleep(CZAS_ODSWIEZANIA);        
      }       
    } 
  }
  return true;
}