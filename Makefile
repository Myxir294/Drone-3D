#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++11

TRGDIR=/tmp/Dron_Podwodny

__start__: ./Dron_Podwodny
	./Dron_Podwodny

./Dron_Podwodny: obj obj/main.o obj/lacze_do_gnuplota.o obj/ProstopadloscianSCN.o obj/Scena.o\
 						obj/Prostopadloscian.o obj/Powierzchnia.o obj/Graniastoslup.o obj/GraniastoslupSCN.o\
						obj/Pret.o obj/PowierzchniaFalowana.o  obj/Dron.o  
	g++ -Wall -pedantic -std=c++11 -o ./Dron_Podwodny obj/main.o\
                        obj/lacze_do_gnuplota.o obj/ProstopadloscianSCN.o obj/Scena.o\
						obj/Prostopadloscian.o obj/Powierzchnia.o obj/Graniastoslup.o obj/GraniastoslupSCN.o\
						obj/Pret.o obj/PowierzchniaFalowana.o obj/Dron.o

obj:
	mkdir -p obj

obj/lacze_do_gnuplota.o: inc/lacze_do_gnuplota.hh src/lacze_do_gnuplota.cpp
	g++ -c ${CXXFLAGS} -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/Prostopadloscian.o: inc/Prostopadloscian.hh src/Prostopadloscian.cpp inc/ObiektSceny.hh
	g++ -c ${CXXFLAGS} -o obj/Prostopadloscian.o src/Prostopadloscian.cpp

obj/ProstopadloscianSCN.o: inc/ProstopadloscianSCN.hh inc/Prostopadloscian.hh src/ProstopadloscianSCN.cpp
	g++ -c ${CXXFLAGS} -o obj/ProstopadloscianSCN.o src/ProstopadloscianSCN.cpp

obj/Graniastoslup.o: inc/Graniastoslup.hh src/Graniastoslup.cpp inc/ObiektSceny.hh
	g++ -c ${CXXFLAGS} -o obj/Graniastoslup.o src/Graniastoslup.cpp

obj/GraniastoslupSCN.o: inc/GraniastoslupSCN.hh inc/Graniastoslup.hh src/GraniastoslupSCN.cpp
	g++ -c ${CXXFLAGS} -o obj/GraniastoslupSCN.o src/GraniastoslupSCN.cpp

obj/Dron.o: inc/Dron.hh inc/ProstopadloscianSCN.hh inc/GraniastoslupSCN.hh src/Dron.cpp
	g++ -c ${CXXFLAGS} -o obj/Dron.o src/Dron.cpp

obj/Pret.o: inc/Pret.hh inc/typy_danych.hh inc/ObiektSceny.hh src/Pret.cpp
	g++ -c ${CXXFLAGS} -o obj/Pret.o src/Pret.cpp

obj/PowierzchniaFalowana.o: inc/PowierzchniaFalowana.hh inc/typy_danych.hh inc/ObiektSceny.hh src/PowierzchniaFalowana.cpp
	g++ -c ${CXXFLAGS} -o obj/PowierzchniaFalowana.o src/PowierzchniaFalowana.cpp

obj/Powierzchnia.o: inc/Powierzchnia.hh inc/typy_danych.hh inc/ObiektSceny.hh src/Powierzchnia.cpp
	g++ -c ${CXXFLAGS} -o obj/Powierzchnia.o src/Powierzchnia.cpp

obj/Scena.o: inc/Scena.hh inc/Dron.hh inc/lacze_do_gnuplota.hh inc/Powierzchnia.hh\
			 inc/PowierzchniaFalowana.hh inc/Pret.hh src/Scena.cpp
	g++ -c ${CXXFLAGS} -o obj/Scena.o src/Scena.cpp

obj/main.o: src/main.cpp inc/Scena.hh
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

clean:
	rm -f obj/*.o ./Dron_Podwodny
