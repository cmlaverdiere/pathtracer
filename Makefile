# TODO Use Cmake (or alt)

CC = clang++
OPT = -Ofast
WARNINGS = -Wall -Weffc++ -Wuninitialized
FLAGS = -g -std=c++11 $(OPT) $(WARNINGS)
LIBPATH = ./lib
INCPATH = ./lib
LIBS = -ltiny_obj_loader -lpng -lpthread -lprofiler

SRC_DIR = ./src
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

pathtracer: $(OBJECTS)
	$(CC) $^ $(FLAGS) -I$(INCPATH) -L$(LIBPATH) $(LIBS) -o $@

.cpp.o:
	$(CC) -c $^ $(FLAGS) -I$(INCPATH) -o $@

clean:
	rm -f pathtracer $(SRC_DIR)/*.o
