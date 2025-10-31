CC = clang
CFLAGS = -Iinclude -Iglthread -Wall -g -std=c11
SRC = src/mm.c glthread/glthread.c src/testapp.c
OBJDIR = build
OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))
.PHONY: all clean run

all: build/test.exe

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/test.exe: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

run: build/test.exe
	./build/test.exe

clean:
	rm -rf build
