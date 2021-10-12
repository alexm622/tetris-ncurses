IDIR=include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=src
LDIR =/usr/local/lib

LIBS=-lm

_DEPS = *.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ =matrix.o encoding.o cipher.o  main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hill-cipher: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
debug: CFLAGS += -DDEBUG -g
debug: hill-cipher

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 