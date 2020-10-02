CC = gcc
CFLAGS = -g -Wall
HEADERS = 
OBJECTS = tema3.o
EXEC = tema3
ARGS = input.in output.out error.out
.PHONY = default build clean

default: build

build: tema3

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

run: build
	./$(EXEC) ${ARGS}

clean:
	-rm -f $(OBJECTS)
	-rm -f $(EXEC)
