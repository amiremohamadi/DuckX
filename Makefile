# WARNING: It is not safe yet!

duckxlib.so: build/handle.o build/pugixml.o build/duckx.o
	g++ -shared -fPIC -o /usr/lib/libduckx.so build/pugixml.o build/duckx.o build/handle.o -lzip
	cp duckx.hpp /usr/include
	cp -r pugixml /usr/include
	cp -r handle /usr/include



build/handle.o: handle/handle.cpp handle/handle.hpp
	g++ -c -fPIC handle/handle.cpp -o build/handle.o

build/pugixml.o: pugixml/pugixml.cpp pugixml/pugixml.hpp pugixml/pugiconfig.hpp
	g++ -c -fPIC pugixml/pugixml.cpp -o build/pugixml.o

build/duckx.o: duckx.cpp duckx.hpp build/handle.o build/pugixml.o
	g++ -c -fPIC duckx.cpp -o build/duckx.o


clean:
	rm -f build/*
	rm -f /usr/include/duckx.hpp
	rm -rf /usr/include/pugixml
	rm -rf /usr/include/handle
	rm -f /usr/lib/libduckx.so

