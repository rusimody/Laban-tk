CFLAGS = -g
CC = gcc
#CXX = i686-w64-mingw32-g++
CXX = g++
executables = led lintel compln prfrm viewc frad3c split3e hideo plotelg shadoq raselr nudes 

all: ${executables}

led: led.cpp
	$(CXX) -I /usr/include/GL led.cpp -o led -lm -lglut -lGL

lintel: lintel.cpp
	$(CXX) -g -I /usr/include/GL lintel.cpp -o lintel -lm -lglut -lGL

compln: compln.c
	$(CC) compln.c -o compln -lm

prfrm:  prfrm.c
	$(CC) prfrm.c -o prfrm -lm

viewc:  viewc.c
	$(CC) viewc.c -o viewc -lm

frad3c:  frad3c.c
	$(CC) frad3c.c -o frad3c

split3e: split3e.c
	$(CC) split3e.c -o split3e

hideo:  hideo.c
	$(CC) hideo.c -o hideo -lm

plotelg:  plotelg.c
	$(CC) plotelg.c -o plotelg -lm

shadoq:  shadoq.c
	$(CC) shadoq.c -o shadoq -lm

raselr:  raselr.c
	$(CC) raselr.c -o raselr -lm

nudes:  nudes.c
	$(CC) $(CFLAGS) nudes.c -o nudes
        #nudes walk -h -j -l 1 -b 4 -G
clean:
	rm -rf $(executables) *.tmp 
