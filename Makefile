CPP = g++
CPPFLAGS = -g -O3 -Wall -Wextra -pedantic -std=c++11 `sdl2-config --cflags`
PKGFLAGS = `sdl2-config --libs`
DEPS = camera.h rays.h world.h objects.h point.h
OBJ = camera.o rays.o world.o objects.o point.o main.o

3DRaytrace: $(OBJ)
	$(CPP) -o $@ $^ $(CPPFLAGS) $(PKGFLAGS)

%.o: %.cpp $(DEPS)
	$(CPP) -c -o $@ $< $(CPPFLAGS)

.PHONY: clean
clean:
	rm *.o 3DRaytrace