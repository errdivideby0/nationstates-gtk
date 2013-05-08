BIN = bin/nationstates-gtk
CC = gcc
CFLAGS=-O3 -pedantic -Wall
OBJ_DIR = ./obj
SRC_DIR = ./src
INC=`pkg-config --cflags --libs gtk+-3.0` --std=c11

OBJECTS = main.o reading.o
OBJECT_PATHS = $(patsubst %,$(OBJ_DIR)/%,$(OBJECTS))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(INC) -o $@ $< $(CFLAGS)

$(BIN): $(OBJECT_PATHS)
	ar rvs $(BIN) $^

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN)

install:
	cp $(OUT) /usr/$(OUT)
