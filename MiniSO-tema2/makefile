CC = gcc
CFLAGS = -g -Wall
HEADERS = 
OBJECTS = tema2.o
EXEC = tema2
ARGS = in_file out_file

.PHONY = default build clean

default: build

build: tema2

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

run: build
	./$(EXEC) ${ARGS}

clean:
	-rm -f $(OBJECTS)
	-rm -f $(EXEC)
