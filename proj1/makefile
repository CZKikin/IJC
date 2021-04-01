CC=gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -lm

all: primes primes-i

run: primes primes-i
	./primes; ./primes-i

primes: eratosthenes.o error.o bitset.h
	$(CC) $(CFLAGS) -O2 eratosthenes.o error.o primes.c -o primes

primes-i: eratosthenes.o error.o bitset.h
	$(CC) $(CFLAGS) -DUSE_INLINE eratosthenes.o error.o primes.c -o primes-i -O0

ppm.o: ppm.h ppm.c
	$(CC) -c $(CFLAGS) ppm.c ppm.h

eratosthenes.o: eratosthenes.c eratosthenes.h
	$(CC) -c $(CFLAGS) eratosthenes.c eratosthenes.h

error.o: error.c error.h
	$(CC) -c $(CFLAGS) error.c error.h

clean:
	rm *.o *.h.gch primes primes-i steg-decode
