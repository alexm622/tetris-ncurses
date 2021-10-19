IDIR=include
CC=gcc
WARNINGS= -Wall -Wextra -Wshadow -Wswitch-enum -Wstack-protector -Wdate-time -Walloc-zero -Walloca -Wimplicit-function-declaration
CFLAGS=-I$(IDIR) -D_XOPEN_SOURCE_EXTENDED $(WARNINGS) -std=c99

ODIR=src
LDIR =/usr/local/lib

LIBS=-lm -lncursesw 

_DEPS = *.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ =main.o blocks.o gui.o game.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tetris: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
debug: CFLAGS += -DDEBUG -g
debug: tetris

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm tetris
