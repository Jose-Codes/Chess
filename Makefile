CC=gcc
CFLAGS=-I. -g -w
DEPS = chess.h
OBJ = chess.o capture.o move.o show.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

chess: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
