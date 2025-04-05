CC = gcc

LIBS = -lraylib -lgdi32 -lwinmm

SRC = main.c
OUT = brick_breaker.exe


all: $(OUT)

$(OUT): $(SRC)
	$(CC) -o $(OUT) $(SRC) $(LIBS)

clean:
	rm -f $(OUT)