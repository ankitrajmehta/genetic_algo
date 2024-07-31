#for linux: g++ -I src/include/SDL2 main.cpp -L src/include/SDL2 -lSDL2 -o main 
all:
	g++ -I src/include -L src/lib -o main main.cpp  -lmingw32 -lSDL2main -lSDL2
	g++ -I src/include -L src/lib -o main main.cpp  -lmingw32 -lSDL2main -lSDL2 -lSDL2_image 