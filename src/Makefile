CFLAGS = -g

all:	led lintel compln prfrm viewc frad3c split3e hideo plotelg nudes

led: led.cpp
	g++ -I /usr/include/GL led.cpp -o led -lm -lglut -lGL

lintel: lintel.cpp
	g++ -g -I /usr/include/GL lintel.cpp -o lintel -lm -lglut -lGL

compln: compln.c
	gcc compln.c -o compln -lm

prfrm:  prfrm.c
	gcc prfrm.c -o prfrm -lm

viewc:  viewc.c
	gcc viewc.c -o viewc -lm

frad3c:  frad3c.c
	gcc frad3c.c -o frad3c

split3e:  split3e.c
	gcc split3e.c -o split3e

hideo:  hideo.c
	gcc hideo.c -o hideo -lm

plotelg:  plotelg.c
	gcc plotelg.c -o plotelg -lm

nudes:  nudes.c
	gcc $(CFLAGS) nudes.c -o nudes
        #nudes walk -h -j -l 1 -b 4 -G
clean:
	rm led lintel compln prfrm viewc frad3c split3e hideo plotelg nudes
