CFLAGS := -std=c11 -g3 -Wall -Wextra -pedantic -fsanitize=undefined,address

BINARIES := src/main.c src/test.c
SOURCES := $(filter-out $(BINARIES), $(wildcard src/*.c))

.PHONY: clean docs
all: test main

clean: 
	@-rm -r bin

main: $(SOURCES)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(SOURCES) src/main.c -o bin/main

test: $(SOURCES)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(SOURCES) src/test.c -o bin/test
	@bin/test

docs: 
	@doxygen
	xdg-open docs/html/index.html