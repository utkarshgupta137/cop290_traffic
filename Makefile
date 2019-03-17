CC = g++
CFLAGS = -Wall
OBJECTS = main.o parser.o simulate.o
OPENGL = `pkg-config --libs --static gl` -lglut

main.out: $(OBJECTS)
	$(CC) $(CFLAGS) -o main.out $(OBJECTS) $(OPENGL)
	$(RM) $(OBJECTS)

main.o:
	$(CC) $(CFLAGS) -c main.cpp
parser.o:
	$(CC) $(CFLAGS) -c parser.cpp
simulate.o:
	$(CC) $(CFLAGS) -c simulate.cpp
