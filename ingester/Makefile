SRC := main.cc

CC := g++
CCFLAGS := -std=c++17 -Wall

BINARY_NAME = ingest

all: $(SRC)
	bear -- $(CC) $(CCFLAGS) $(SRC) -o $(BINARY_NAME)

ingest: all
	./ingest
