CC      = gcc
CFLAGS  = $(shell pkg-config --cflags gtk+-3.0)
LIBS    = $(shell pkg-config --libs gtk+-3.0)

AA_Homework1: main.c
	$(CC) main.c -o AA_Homework1 $(CFLAGS) $(LIBS)

clean:
	rm -f AA_Homework1
