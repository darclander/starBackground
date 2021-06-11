OBJS = ./src/*.cpp

HEADERS =  -I./src/headers
OBJ_NAME = ./debug/a
INCLUDE = -ID:\programming\i686-w64-mingw32\include
LIBRARY = -LD:\programming\i686-w64-mingw32\lib
THEL = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_Image -lpthread

all : $(OBJS)
	g++ $(OBJS) $(INCLUDE) $(HEADERS) $(LIBRARY) $(THEL) -o $(OBJ_NAME)
