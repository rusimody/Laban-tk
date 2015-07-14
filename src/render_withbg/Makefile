CFLAGS = -g
CC = gcc
#CXX = i686-w64-mingw32-g++
CXX = g++
executables = led lintel lintelref

all: ${executables}

led: led.cpp
	$(CXX) -I /usr/include/GL led.cpp -o led -lm -lglut -lGL

lintel: lintel.cpp
	$(CXX) -g -I /usr/include/GL lintel.cpp -o lintel -lm -lglut -lGL

lintelref: lintelref.cpp
	$(CXX) -g -I /usr/include/GL lintel.cpp -o lintelref -lm -lglut -lGL
