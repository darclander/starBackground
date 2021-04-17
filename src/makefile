OBJS = main.cpp ui.cpp star.cpp parallel.cpp imgplayer.cpp

HEADERS =  -I./headers
OBJ_NAME = ./a
INCLUDE = -IC:\MinGW\i686-w64-mingw32\include
LIBRARY = -LC:\MinGW\i686-w64-mingw32\lib
THEL = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_Image -lpthread

all : $(OBJS)
	g++ $(OBJS) $(INCLUDE) $(HEADERS) $(LIBRARY) $(THEL) -o $(OBJ_NAME)
