CC=clang++
FLAGS=-g -Wall -std=c++11
LIBPATH=./lib
INCPATH=./lib
LIBS=-ltiny_obj_loader -lpng

pathtracer: pathtracer.cpp
	$(CC) $^ $(FLAGS) -I$(INCPATH) -L$(LIBPATH) $(LIBS) -o $@
