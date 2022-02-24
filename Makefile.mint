PREFIX=m68k-atari-mint
CC=$(PREFIX)-gcc

CFLAGS=-std=gnu99 -Wall -Os -mshort -Wno-array-bounds -Wno-misleading-indentation

LIBCMINI_DIR=$(HOME)/src/libcmini/build
LINK=-nostdlib $(LIBCMINI_DIR)/minicrt0.o $< -L$(LIBCMINI_DIR)/mshort $(LDFLAGS) -lcmini -lgcc -o $@

TARGETS=curdle.tos

src = $(wildcard *.c)
obj = $(src:.c=.o)

.PHONY: all clean
all: $(TARGETS)
clean:
	rm -f $(TARGETS) $(obj)

curdle.tos: $(obj)
	$(CC) $(LDFLAGS) $(LINK)
	$(PREFIX)-objdump -drwC $@ > $@.s
	$(PREFIX)-strip -s $@
	@$(PREFIX)-size $@
	@du -b $@
