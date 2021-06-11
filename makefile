OBJS = ./src/*.cpp

INC_PATH = -ID:\programming
LIB_PATH = -LD:\programming

HEADERS =  -I./src/headers
OBJ_NAME = ./debug/starbg
INCLUDE = $(INC_PATH)\i686-w64-mingw32\include
LIBRARY = $(LIB_PATH)\i686-w64-mingw32\lib
THEL = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_Image -lpthread

all : $(OBJS)
	g++ $(OBJS) $(INCLUDE) $(HEADERS) $(LIBRARY) $(THEL) -o $(OBJ_NAME)
