BIN = bin/nationstates-gtk
CC = gcc
CFLAGS=-O3 -pedantic -Wall --std=c11
OBJ_DIR = obj
SRC_DIR = src
INC=`pkg-config --cflags --libs gtk+-3.0 libcurl`

OBJECTS = main.o reading.o
OBJECT_PATHS = $(patsubst %,$(OBJ_DIR)/%,$(OBJECTS))

all: $(OBJECT_PATHS)
	$(CC) $(INC) $(OBJECT_PATHS) -o $(BIN) $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(INC) -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN)

install:
	cp $(OUT) /usr/$(OUT)
