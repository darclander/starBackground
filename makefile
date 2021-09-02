OBJS = ./src/*.cpp

# Change these paths to wherever your 'i686-w64-mingw32' folder is. 
# In my scenario it is in D:\programming\i686-w64-mingw32 and therefore the line should be: -ID:\programming   
INC_PATH = -IC:\MinGW
LIB_PATH = -LC:\MinGW

HEADERS =  -I./src/headers
OBJ_NAME = ./debug/starbg
INCLUDE = $(INC_PATH)\i686-w64-mingw32\include
LIBRARY = $(LIB_PATH)\i686-w64-mingw32\lib
THEL = -lmingw32 -lSDL2main -lSDL2 -lSDL2_Image

all : $(OBJS)
	g++ $(OBJS) $(INCLUDE) $(HEADERS) $(LIBRARY) $(THEL) -o $(OBJ_NAME)
