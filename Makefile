CC=clang++
OPT=-O3
FLAGS=-g -std=c++11 $(OPT) $(WARNINGS)
WARNINGS= -Wall -Weffc++ -Wuninitialized
LIBPATH=./lib
INCPATH=./lib
LIBS=-ltiny_obj_loader -lpng

pathtracer: pathtracer.cpp
	$(CC) $^ $(FLAGS) -I$(INCPATH) -L$(LIBPATH) $(LIBS) -o $@
