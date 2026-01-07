CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm

SRC = repl.c lexer.c parseur.c evaluation.c pile.c symbols.c
OBJ = $(SRC:.c=.o)
TARGET = repl

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
