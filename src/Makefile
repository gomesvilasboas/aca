CC=gcc
FLAGS=-lm -fopenmp -O3 -Wimplicit-function-declaration -Wunused-result -ffast-math -march=native
DEBUGFLAGS=-g
RM=rm -f

EXEC=ACA

.PHONY : all clean debug

all:
	$(CC) $(FLAGS) ACA.c -c
	$(CC) $(FLAGS) read_csv.c -c
	$(CC) $(FLAGS) ant.c -c
	$(CC) $(FLAGS) distance.c -c
	$(CC) $(FLAGS) grid.c -c
	$(CC) $(FLAGS) ACA.o read_csv.o ant.o distance.o grid.o -o $(EXEC)

debug: $(EXEC).c
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).c -o $(EXEC)

clean:
	$(RM) *.o $(EXEC)
