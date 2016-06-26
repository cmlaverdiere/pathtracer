CC=clang++
OPT=
FLAGS=-g -Wall -std=c++11 $(OPT)
LIBPATH=./lib
INCPATH=./lib
LIBS=-ltiny_obj_loader -lpng

pathtracer: pathtracer.cpp
	$(CC) $^ $(FLAGS) -I$(INCPATH) -L$(LIBPATH) $(LIBS) -o $@
