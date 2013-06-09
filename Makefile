CC=clang
LD=clang++
CFLAGS=-g -Wall -I$(shell pg_config --includedir)
LDFLAGS=-L$(shell pg_config --libdir) -pthread -lpq -lmicrohttpd

all: creadings

cppreadings: creadings.c

.PHONY: clean

clean:
	rm -rf *.o *.dSYM creadings
