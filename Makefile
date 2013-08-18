CC 				:= gcc
CC_FLAGS 	:= -g -Wall -fPIC -shared
SRC 			:= squib.c
TARGET 		:= squib

all: squib.c
	$(CC) $(CC_FLAGS) $(SRC) -o $(TARGET)

clean:
	rm $(TARGET)
