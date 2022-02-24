CFLAGS=-Wall -Ofast -Wno-array-bounds -Wno-misleading-indentation

src = $(wildcard *.c)
obj = $(src:.c=.o)

TARGETS=wordlist.h curdle

.PHONY: all clean
all: $(TARGETS)
clean:
	rm -f $(TARGETS) $(obj)

curdle: curdle.o wordlist.h
	$(CC) $^ $(LDFLAGS) -o $@

wordlist.h: wordlist.txt list2h.pl
	./list2h.pl < $< > $@
