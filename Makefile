CC_FLAGS  := -g -ansi -pedantic -std=c99 -Wall -fPIC -shared
SRC       := squib.c pearson.c classifier.c
TARGET    := squib

ifeq ($(CC),clang)
	CC_FLAGS := $(CC_FLAGS) -Weverything
else
  CC_FLAGS := $(CC_FLAGS) -Werror
endif

all: squib.c
	$(CC) $(CC_FLAGS) $(SRC) -o $(TARGET) -lm

clean:
	rm $(TARGET)
