INCLUDE_DIR := include
SRC := src/*.cc
INCLUDE := $(INCLUDE_DIR)/*.h

CC := g++
CCFLAGS := -std=c++17 -Wall

BINARY_NAME := order_manager

all: $(SRC) $(INCLUDE)
	bear -- $(CC) $(CCFLAGS) $(SRC) -I$(INCLUDE_DIR) -o $(BINARY_NAME)
