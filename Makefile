
BIN ?= hearthstone-cardxml
PREFIX ?= /usr/local
CFLAGS = -Wall -Wextra

all: $(BIN)

$(BIN): hearthstone-cardxml.c
	$(CC) -o $@ $^

install: $(BIN)
	install $< $(PREFIX)/bin

clean:
	rm -f $(BIN)

