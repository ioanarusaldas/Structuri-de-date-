CC=gcc

lab5: test.o liste.o hash.o
	$(CC) $^ -o $@

test.o: testHash.c
	$(CC) $^ -c -o $@

hash.o: functii-tabHash.c
	$(CC) $^ -c -o $@

liste.o: functiiLG.c
	$(CC) $^ -c -o $@

clean:
	rm lab5 *.o


