# makefile variables
CC = g++
CFLAGS = -Wall -std=c++11
INLCUDES = -I./third-party
LIBS = -L./third-party/SDL2/lib/x64 -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image -lSDL2_mixer

# target 
SRCS = src/main.cpp src/game.cpp \
	   src/logger/Logger.cpp \
	   src/widgets/Button.cpp 
OBJ = main


all: build run
build:
	$(CC) -o $(OBJ) $(SRCS) $(INLCUDES) $(LIBS) $(CFLAGS)

run:
	./$(OBJ).exe

clean:
	-rm $(OBJ).exe