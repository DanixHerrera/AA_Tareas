# Makefile of Homework 1 - Analysis of Algorithms
# Daniel Josué Herrera Córdoba
# Adrian Rodríguez Quirós

CC      = gcc
CFLAGS  = -Wall -Wextra -g $(shell pkg-config --cflags gtk+-3.0)
LIBS    = $(shell pkg-config --libs gtk+-3.0)
TARGET  = AA_Homework1
SRC = main.c displayChart.c


$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LIBS)

run: $(TARGET)
	./$(TARGET)
	
clean:
	rm -f $(TARGET)
	
.PHONY: run clean
