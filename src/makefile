IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = catalog.h data.h log.h movie.h tree.h ui.h user.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o catalog.o data.o log.o movie.o tree.o ui.o user.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -Wall -Wextra -g -std=c11 -ggdb3 -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~