# TODO Use Cmake (or alt)

CC = clang++
OPT = -Ofast
WARNINGS = -Wall -Weffc++ -Wuninitialized
FLAGS = -g -std=c++11 $(OPT) $(WARNINGS)
LIBS = -ltiny_obj_loader -lpng -lpthread -lprofiler -lSOIL
GLLIBS = -lGL -lGLU -lGLEW -lglfw
XLIBS = -lX11 -lXxf86vm -lXrandr -lXi

SRC_DIR = ./src
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

LIBPATH = $(SRC_DIR)/lib
INCPATH = $(SRC_DIR)/lib

pathtracer: $(OBJECTS)
	$(CC) $^ $(FLAGS) -I$(INCPATH) -L$(LIBPATH) $(GLLIBS) $(XLIBS) $(LIBS) -o $@

.cpp.o:
	$(CC) -c $^ $(FLAGS) -I$(INCPATH) -o $@

clean:
	rm -f pathtracer $(SRC_DIR)/*.o
