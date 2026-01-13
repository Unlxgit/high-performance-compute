CC      := gcc
CFLAGS  := -O3
LDFLAGS := -lm

SRC := main.c

.PHONY: all clean

all: pi_openmp

pi_openmp: $(SRC)
	$(CC) $(CFLAGS) -fopenmp $< -o $@ $(LDFLAGS)

clean:
	rm -f pi_openmp
