CC_FLAGS  := -g -ansi -pedantic -std=c99 -Wall -fPIC -shared -Werror
SRC       := squib.c pearson.c classifier.c
TARGET    := squib

ifeq ($(CC),clang)
	CC_FLAGS := $(CC_FLAGS) -Weverything
endif

all: squib.c
	$(CC) $(CC_FLAGS) $(SRC) -o $(TARGET) -lm

clean:
	rm $(TARGET)
