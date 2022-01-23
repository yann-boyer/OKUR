mkdir bin
g++ -I include/ src/*.cpp -s -Wall -Wextra -O3 `sdl2-config --cflags` -o bin/okur `sdl2-config --libs`
