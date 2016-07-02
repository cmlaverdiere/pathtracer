# TODO Use Cmake (or alt)

CC = clang++
OPT = -O3
WARNINGS = -Wall -Weffc++ -Wuninitialized -Qunused-arguments
FLAGS = -g -std=c++11 $(OPT) $(WARNINGS)
LIBPATH = ./lib
INCPATH = ./lib
LIBS = -ltiny_obj_loader -lpng

SRC_DIR = ./src
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

pathtracer: $(OBJECTS)
	$(CC) $^ $(FLAGS) -I$(INCPATH) -L$(LIBPATH) $(LIBS) -o $@

.cpp.o:
	$(CC) -c $^ $(FLAGS) -I$(INCPATH) -L$(LIBPATH) $(LIBS) -o $@

clean:
	rm -f pathtracer $(SRC_DIR)/*.o
