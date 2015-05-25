CC_FLAGS  := -g -ansi -pedantic -std=c99 -Wall -fPIC -shared
SRC       := squib.c pearson.c classifier.c
TARGET    := squib
BATS_DIR  := /tmp/bats

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

bats:
	@[ -d $(BATS_DIR) ] || git clone https://github.com/sstephenson/bats.git $(BATS_DIR)

test: squib bats
	@$(BATS_DIR)/bin/bats tests/
