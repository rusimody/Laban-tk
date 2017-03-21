CC = gcc
CXX = g++
CFLAGS = -g -Wall -lm
CPPFLAGS = -g -I /usr/include/GL
CPPLIBS = -lm -lglut -lGL

# Add or Remove fileNames below if necessary
Cfiles = compln prfrm viewc frad3c split3e shadoq raselr nudes
CPPfiles = led lintel lintelref

all: c cpp
c: $(Cfiles)
%: %.c
	$(CC) $(CFLAGS) -o $@ $<
cpp: $(CPPfiles)
%: %.cpp
	$(CXX) $(CPPFLAGS) -o $@ $< $(CPPLIBS)

clean:
	rm -rf $(Cfiles) $(CPPfiles) *.tmp 
