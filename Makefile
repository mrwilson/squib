CC        := gcc
CC_FLAGS  := -g -ansi -pedantic -std=c99 -Wall -fPIC -shared
SRC       := squib.c functions/*.h
TARGET    := squib

all: squib.c
	$(CC) $(CC_FLAGS) $(SRC) -o $(TARGET) -lm

clean:
	rm $(TARGET)
