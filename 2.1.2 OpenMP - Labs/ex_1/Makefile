# Simple build rules for pi midpoint integration

CC      := gcc
CFLAGS  := -O3
LDFLAGS := -lm

SRC := main.c

.PHONY: all serial auto clean

all: serial

serial: pi_serial

auto: pi_auto

pi_serial: $(SRC)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Auto-parallelize loop with GCC; adjust thread count by changing t value below
pi_auto: $(SRC)
	$(CC) $(CFLAGS) -ffast-math -ftree-parallelize-loops=4 $< -o $@ $(LDFLAGS)

clean:
	rm -f pi_serial pi_auto
