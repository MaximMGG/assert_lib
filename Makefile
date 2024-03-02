BINARY = assert
STATIC_LIB = libassert.a
CC = gcc
FLAGS = 
DEBUG = -g
LIBS =  -l_util
SRC = ./src/assert.c
OBJ = $(patsubst %.c, %.o, $(SRC))

all: $(STATIC_LIB)

$(STATIC_LIB): $(OBJ)
	ar rcs $@ $^
$(BINARY): $(OBJ)
	$(CC) -o $(BINARY) $^ $(FLAGS) $(LIBS) $(DEBUG)
%.o: %.c
	$(CC) -o $@ -c $< $(FLAGS) $(LIBS) $(DEBUG)
clean: 
	rm $(BINARY) $(OBJ) $(STATIC_LIB)

deploy:
	sudo cp $(STATIC_LIB) /usr/lib/
	sudo cp headers/assert.h /usr/include/
