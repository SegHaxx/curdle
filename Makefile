CFLAGS=-std=gnu99 -Wall -Ofast -Wno-array-bounds -Wno-misleading-indentation

src = $(wildcard *.c)
obj = $(src:.c=.o)

TARGETS=curdlist.h curdle

.PHONY: all clean
all: $(TARGETS)
clean:
	rm -f $(TARGETS) $(obj)

curdle: curdle.o curdlist.h
	$(CC) $^ $(LDFLAGS) -o $@

curdlist.h: wordlist.txt list2h.pl
	./list2h.pl < $< > $@
