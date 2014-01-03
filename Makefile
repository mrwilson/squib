CC_FLAGS  := -g -ansi -pedantic -std=c99 -Wall -fPIC -shared
SRC       := squib.c pearson.c classifier.c
TARGET    := squib

TESTS     := ./run_tests.sh

ifeq ($(CC),clang)
	CC_FLAGS := $(CC_FLAGS) -Weverything
else
  CC_FLAGS := $(CC_FLAGS) -Werror
endif

all: squib

squib: squib.c
	$(CC) $(CC_FLAGS) $(SRC) -o $(TARGET) -lm

clean:
	@rm -f $(TARGET)

test: squib
	@$(TESTS)
