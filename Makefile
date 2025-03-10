all: build run
build:
	g++ -o main src/*.cpp -I./third-party -L./third-party/SDL2/lib/x64 -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image -lSDL2_mixer -Wall -std=c++11

run:
	./main.exe

clean:
	-rm main.exe