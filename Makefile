
OBJS = ./src/*.cpp

CC=g++

OPTIMIZATION= #-O2

NANA_FLAGS=-lgdi32 -lcomdlg32 -ljpeg -lpng
FFMPEG_FLAGS=-lavformat -lavcodec -lavutil
LIBS= -lmingw32 -lSDL2main -lSDL2 -lSDL2_Image $(NANA_FLAGS) $(FFMPEG_FLAGS)


IDIR = ./src/headers
CFLAGS= -I$(IDIR) $(LIBS) $(EXTRA_LIBS)
DEPS = $(wildcard $(IDIR)/*.hpp)

IDIR = ./src/headers
_DEPS = star.hpp ui.hpp videoplayer.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = ./obj
_OBJ = main.o star.o ui.o videoplayer.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: starBG

$(ODIR)/%.o: ./src/%.cpp $(DEPS)
	$(CC) -c $(OPTIMIZATION) -o $@ $< -I./src/headers

starBG: $(OBJ)
	$(CC) -O3 -o ./bin/$@ $^ $(CFLAGS)

run: starBG
	./bin/starBG

clean:
	rm -f obj/*
	rm -f bin/starBG.exe

install:
	mkdir -p bin/

.PHONY: install clean
