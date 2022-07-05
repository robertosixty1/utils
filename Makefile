CFLAGS = -Wall -Wextra -std=c11 -pedantic -ggdb

all: ./bin/cp

bin:
	mkdir -p ./bin

./bin/cp: bin cp.c
	$(CC) $(CFLAGS) -o ./bin/cp cp.c
