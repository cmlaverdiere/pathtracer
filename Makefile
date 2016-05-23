CC=clang++
FLAGS=-g -Wall
LIBPATH=./lib
INCPATH=./lib
LIBS=-ltiny_obj_loader

pathtracer: pathtracer.cpp
	$(CC) $^ $(FLAGS) -I$(INCPATH) -L$(LIBPATH) $(LIBS) -o $@
