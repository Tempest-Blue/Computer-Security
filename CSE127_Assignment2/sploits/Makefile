# tools
CC := gcc
RM := rm -f

# flags
CFLAGS := -ggdb -Wall
LDFLAGS :=
LDLIBS :=

# sources
sources := sploit0.c sploit1.c sploit2.c sploit3.c sploit4.c
sploits := $(sources:.c=)

# gmake magic
.PHONY: all clean

#sploits
all: $(sploits)

clean:
	$(RM) $(sploits)

#dependencies
$(sploits): shellcode.h
