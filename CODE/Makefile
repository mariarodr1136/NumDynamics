CC = gcc
CFLAGS = -Wall
PYTHON_SCRIPT = histogram_generator.py
PYTHON = python3

all: random_gen stats run.sh

random_gen: random_gen.c
	$(CC) $(CFLAGS) random_gen.c -o random_gen -lm

stats: stats.c
	$(CC) $(CFLAGS) stats.c -o stats -lm

run.sh:
	echo '#!/bin/bash' > ass1
	echo 'rm -rf HISTOGRAM' >> ass1
	echo './random_gen' >> ass1
	echo './stats' >> ass1
	echo '$(PYTHON) $(PYTHON_SCRIPT)' >> ass1
	chmod +x ass1

clean:
	rm -f random_gen stats ass1
	rm -rf DATA HISTOGRAM
