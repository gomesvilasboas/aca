CC=g++
FLAGS=-lm -fopenmp -O3 -ffast-math -march=native# -fpermissive
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
	$(CC) $(FLAGS) group.c -c
	$(CC) $(FLAGS) ACA.o read_csv.o ant.o distance.o grid.o group.o -o $(EXEC)
	$(RM) *.o

debug: $(EXEC).c
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).c -o $(EXEC)

clean:
	$(RM) *.o $(EXEC)
