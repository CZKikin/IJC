CC=gcc
CFLAGS=-g -std=c99 -pedantic -Wall -Wextra

all: tail wordcount wordcount-d

tail: tail.c
	$(CC) $(CFLAGS) tail.c -o tail

wordcount: wordcount.c htab.a io.o
	$(CC) $(CFLAGS) $^ -o $@ 

wordcount-d: wordcount.c htab.so io.o
	$(CC) $(CFLAGS) $^ -o $@

io.o: io.c io.h
	$(CC) $(CFLAGS) -c $< 

htab.a: htab.o
	ar rcs $@ $< 

htab.so: htab.o
	LD_LIBRARY_PATH=".:$LD_LIBRARY_PATH" $(CC) $(CFLAGS) -fPIC -shared $^ -o $@

htab.o: htab.c htab.h htabPrivate.h
	$(CC) -fPIC -c $(CFLAGS) $<
clean:
	rm *.o *.h.gch wordcount tail wordcount-d *.so *.a
