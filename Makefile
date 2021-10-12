IDIR=include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=src
LDIR =/usr/local/lib

LIBS=-lm

_DEPS = *.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ =main.0
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