libczi = ~/Documents/libraries/libczi/build/src/libCZI/liblibCZI.dylib
libczih = ~/Documents/libraries/libczi/Src/libCZI

all:
	g++ -std=c++0x main.cpp $(libczi) -o cttf -I $(libczih)
