CC = gcc
CFLAGS = -Wall -I./include/

client:
	$(CC) $(CFLAGS) -o client client.c helpers.c buffer.c requests.c

clean:
	rm client

build: client

check: build run-check clean

run-check:
	python3 ./checker/checker.py ./client
