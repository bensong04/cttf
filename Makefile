libczi = ~/Documents/libraries/libczi/build/src/libCZI
libczih = ~/Documents/libraries/libczi/Src/libCZI
headers = .
src = MultiThreadedTrans.cpp CTTFUtils.cpp

all:
	g++ -std=c++20 main.cpp $(src) $(libczi)/liblibCZI.dylib -o cttf -I $(headers) -I $(libczih)
	install_name_tool -add_rpath $(libczi) cttf
