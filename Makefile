CC = clang
CFLAGS = -Iinclude -Wall -g
SRC = src/heap.c
OBJ = $(SRC:.c=.o)

all: build/example_run

build/example_run: $(OBJ) examples/example_run.c
	$(CC) $(CFLAGS) -o $@ $^

test: $(OBJ) tests/test_calloc_free.c
	$(CC) $(CFLAGS) -o build/test_heap $^
	./build/test_heap

clean:
	rm -rf build/*.o build/example_run build/test_heap

run-example: src/heap.o
	$(CC) $(CFLAGS) -o build/example_run src/heap.o examples/example_run.c
	./build/example_run
