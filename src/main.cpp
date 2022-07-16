#include <iomanip>
#include "Scena.hh"

using namespace std;


/*!
 * \file  
 * \brief Zawiera funkcje main
 *
 *  Plik zawiera kod zrodlowy funkcji main sterujacej przeplywem programu.
 *  Program rozpoczyna swoje dzialanie inicjalizacja sceny, powodujacej
 *  narysowanie stanu poczatkowego obiektow. Nastepnie udostepnia menu
 *  uzytkownika, za pomoca ktorego uzytkownik moze nakazac dronowi wykonac
 *  ruch do przodu z okreslolnym katem opadania lub obrot wokol osi OZ.
 *  Kazda z tych czynnosci jest odpowiednio animowana na scenie.
 *  
 * \retval -1 - Niepoprawna inicjalizacja sceny
 * \retval 0 - Program wszystkie operacje wykonal poprawnie
 */

int main()
{ 
  int kat_obrotu;
  unsigned int dlugosc_ruchu;
  int kat_z;
  int pom;
  char znak;
  char c;
  Scena Scena;
  if(!Scena.InicjalizujScene())
  {
    cout << "Blad inicjalizacji sceny" << endl;
    Scena.WyczyscListe();    
    return -1;
  }
  znak = 'm';
  while (znak != 'k') /*Menu uzytkownika*/
  {
    switch (znak)
    {
      case ('m'):
      {
        cout << endl << "r - zadaj ruch na wprost" << endl;
        cout << "o - zadaj zmiane orientacji" << endl;
        cout << "m - wyswietl menu" << endl << endl;
        cout << "k - koniec dzialania programu" << endl << endl;
        break;
      }
      case ('r'):
      {
        cout << "Wybierz dlugosc ruchu: " << flush;
        cin >> pom >> noskipws >> c;
        if(pom >= 0)
        {
          dlugosc_ruchu = pom;
        }
        else
        {
          dlugosc_ruchu = 0;
        }
        cout << endl;
        cout << "Wybierz kat zanurzenia/wynurzenia: " << flush;
        cin >> kat_z >> noskipws >> c;
        cout << endl;
        if (!Scena.Animowana_Translacja_Bryly(Scena.Wez_Drona1(), kat_z, dlugosc_ruchu))
        {
          cout << "Nie udalo sie wykonac ruchu lub dalszy ruch jest niemozliwy" << endl;
        }
        break;
      }
      case ('o'):
      {
        cout << "Wybierz kat obrotu: " << flush;
        cin >> kat_obrotu >> noskipws >> c;
        cout << endl;
        if (!Scena.Animowany_Obrot_Bryly(Scena.Wez_Drona1(),kat_obrotu))
        {
          cout << "Nie udalo sie wykonac obrotu lub dalszy obrot jest niemozliwy" << endl;
        }
        break;
      }
      case ('k'):
      { 
        break;
      }
      default:
      { 
        cout << "Nie rozpoznano opcji!" << endl;
        break;
      }
    } 
    cin.clear();
    cout << "Twoj wybor (m - menu): ";
    cin >> skipws >> znak;
  }
  cout << "Koniec dzialania programu" << endl;
  Scena.WyczyscListe();   
  
  return 0;
}
