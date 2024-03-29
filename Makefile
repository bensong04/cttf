libczi = ~/Documents/libraries/libczi/build/src/libCZI
libczih = ~/Documents/libraries/libczi/Src/libCZI
tinytiff = /usr/local/lib
tinytiffh = /usr/local/include
headers = .
src = MultiThreadedTrans.cpp CTTFUtils.cpp
standard = c++20
includes = -I $(headers) -I $(libczih) -I $(tinytiffh)
links = -L $(tinytiff) -lTinyTIFF_Release

all:
	g++ -std=$(standard) main.cpp $(src) $(libczi)/liblibCZI.dylib -o cttf $(includes) $(links)
	install_name_tool -add_rpath $(libczi) cttf
