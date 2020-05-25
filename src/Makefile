#CC=g++
CC=pgc++
#FLAGS=-lm -fopenmp -O3 -ffast-math -march=native# -fpermissive
FLAGS=-lm -mp -O4 -fast -acc=verystrict -Minfo=all -ta=multicore#,tesla:managed
DEBUGFLAGS=-pg
RM=rm -f

EXEC=../bin/ACA

.PHONY : all clean debug

all:
	$(CC) $(FLAGS) $(DEBUGFLAGS) ACA.c -c
	$(CC) $(FLAGS) $(DEBUGFLAGS) read_csv.c -c
	$(CC) $(FLAGS) $(DEBUGFLAGS) ant.c -c
	$(CC) $(FLAGS) $(DEBUGFLAGS) distance.c -c
	$(CC) $(FLAGS) $(DEBUGFLAGS) grid.c -c
	$(CC) $(FLAGS) $(DEBUGFLAGS) group.c -c
	$(CC) $(FLAGS) $(DEBUGFLAGS) ACA.o read_csv.o ant.o distance.o grid.o group.o -o $(EXEC)
	$(RM) *.o

debug: $(EXEC).c
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).c -o $(EXEC)

clean:
	$(RM) *.o $(EXEC)
