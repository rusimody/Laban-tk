all:	led lintel compln prfrm nudes

led: led.cpp
	g++ -I /usr/include/GL led.cpp -o led -lm -lglut -lGL

lintel: lintel.cpp
	g++ -g -I /usr/include/GL lintel.cpp -o lintel -lm -lglut -lGL

compln: compln.c
	gcc compln.c -o compln -lm

prfrm:  prfrm.c
	gcc prfrm.c -o prfrm -lm

nudes:  nudes.c
	gcc nudes.c -o nudes

clean:
	rm led lintel compln prfrm nudes
