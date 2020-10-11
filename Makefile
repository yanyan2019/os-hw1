# Makefile

# default compiler
CC=gcc --std=gnu99
EXE_FILE = movies

$(EXE_FILE): main.c movie.h
	$(CC) -o $(EXE_FILE) main.c

clean:
	rm -f *.o $(EXE_FILE)
