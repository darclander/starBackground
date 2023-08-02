
OBJS = ./src/*.cpp

CC=g++
CFLAGS= -I$(IDIR) -lmingw32 -lSDL2main -lSDL2 -lSDL2_Image -lavformat -lavcodec -lavutil


IDIR = ./src/headers
_DEPS = star.hpp ui.hpp videoplayer.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = ./obj
_OBJ = main.o star.o ui.o videoplayer.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: starBG

./obj/%.o: ./src/%.cpp $(DEPS)
	$(CC) -O3 -c -o $@ $< $(CFLAGS)

starBG: $(OBJ)
	$(CC) -O3 -o ./debug/$@ $^ $(CFLAGS) 

run: starBG
	./debug/starBG

clean:
	del /s *.o
	del starBG.exe
