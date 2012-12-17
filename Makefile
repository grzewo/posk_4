CC = gcc
FILE = nadajnik.c 
FILE2 = odbiornik.c
CFLAGS = -g -Wall -o
OUT = nadajnik
OUT2 = odbiornik

rebuild: clean build

build: $(FILE) $(FILE2)
	$(CC) $(CFLAGS)  $(OUT) $(FILE)
	$(CC) $(CFLAGS)  $(OUT2) $(FILE2)

clean:
	-rm -f *.o
	-rm /tmp/moje_fifo
