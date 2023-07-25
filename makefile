
OBJS = ./src/*.cpp

CC=g++
CFLAGS= -I$(IDIR) -lmingw32 -lSDL2main -lSDL2 -lSDL2_Image -lavformat


IDIR = ./src/headers
_DEPS = star.hpp ui.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = ./obj
_OBJ = main.o star.o ui.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: starBG

./obj/%.o: ./src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

starBG: $(OBJ)
	$(CC) -o ./debug/$@ $^ $(CFLAGS)

run: starBG
	./debug/starBG

clean:
	del /s *.o
	del starBG.exe
