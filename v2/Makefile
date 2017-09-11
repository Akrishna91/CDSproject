.PHONY: all clean
CC=clang
CPP=g++-5
AR=ar
RANLIB=ranlib
CFLAGS= -g -Wall -Wno-unused-function
C11FLAGS= -g -Wall -Wno-unused-function -std=c++11
SRCDIR = ./src
INCLUDEDIR = -I./include -I.
DEPS = 
LIBS = -lm

PROGRAMS = main

all: $(PROGRAMS)

main:  $(SRCDIR)/*.cpp
	$(CPP) $(C11FLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

clean:
	rm -rf $(PROGRAMS) *.dSYM

