CC = gcc
CFLAGS = -g -Wall
HEADERS = 
OBJECTS = atm.o
EXEC = atm

.PHONY = default build clean

default: build

build: atm

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

run: build
	./$(EXEC) ${ARGS}

clean:
	-rm -f $(OBJECTS)
	-rm -f $(EXEC)
