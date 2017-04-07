CFLAGS = -g

CC = gcc

CXX = g++

executables = lintel lintelref

all: ${executables}

lintel: lintel.cpp
	$(CXX) -g -I /usr/include/GL lintel.cpp -o lintel -lm -lglut -lGL

lintelref: lintelref.cpp
	$(CXX) -g -I /usr/include/GL lintelref.cpp -o lintelref -lm -lglut -lGL

clean:
	rm -rf $(executables) *.tmp 

