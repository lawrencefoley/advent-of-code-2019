# Makefile
.PHONY: clean
CC = gcc
CCFLAGS = -g

SOURCES =  day02.c vector.c vector.h

OBJECTS = $(SOURCES:%.cpp=%.o)
%.o:%.c
	@$(CC) $(CCFLAGS) -c $< -o $@

day02: $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf day02 *.o
