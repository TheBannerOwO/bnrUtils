CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -g
TESTFLAGS = -L$(LIB_DIR)/ -l$(LIBNAME)
VALFLAGS = --leak-check=full --show-reachable=yes --track-origins=yes

LIBNAME = BnrDatastructures
DEST = ~/mylibs/

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
INC_DIR = include
TES_DIR = tests

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBRARY = $(LIB_DIR)/lib$(LIBNAME).a

TEST_SOURCES = $(wildcard $(TES_DIR)/*.c)
TEST_EXECS = $(TEST_SOURCES:$(TES_DIR)/%.c=$(TES_DIR)/%.out)

all: $(LIBRARY) $(TEST_EXECS)

rebuild: clean all

library: $(LIBRARY)

tests: $(TEST_EXECS)

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR) $(TES_DIR)/*.out

$(TES_DIR)/%.out: $(TES_DIR)/%.c | $(LIBRARY)
	$(CC) $(CFLAGS) $< $(TESTFLAGS) -o $@
	@valgrind $(VALFLAGS) --log-file="$@.log" $@

$(LIBRARY): $(OBJECTS) | $(LIB_DIR)
	@ar rcs $@ $^
	@cp -a $@ $(DEST)
	@cp $(INC_DIR)/*.h /usr/include/myheaders/

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIB_DIR):
	@mkdir -p $(LIB_DIR)


.PHONY: all clean library tests rebuild