CC = gcc
CXX = g++
CFLAGS = -g -Wall -lm -o
CPPFLAGS = -g -I /usr/include/GL -lm -lglut -lGL -o 

# Add or Remove fileNames below if necessary
Cfiles = compln prfrm viewc frad3c split3e shadoq raselr nudes
CPPfiles = led lintel lintelref

all: c cpp
c: $(Cfiles)
%: %.c
	$(CC) $(CFLAGS) $@ $<
cpp: $(CPPfiles)
%: %.cpp
	$(CXX) $(CPPFLAGS) $@ $<

clean:
	rm -rf $(Cfiles) $(CPPfiles) *.tmp 
