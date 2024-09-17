all:
	g++ -Isrc/include -Lsrc/lib -static-libgcc -static-libstdc++ -o C:\Users\petes\OneDrive\Desktop\platformerAlpha\main.exe main.cpp -lmingw32 -lSDL2main -lSDL2