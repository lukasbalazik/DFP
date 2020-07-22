CC=gcc
CFLAGS=-Wall -O3 -Ofast -Iinclude -Itests
OBJ=src/DFP/ipv4.o src/DFP/domain.o src/DFP/hash.o src/vector.o tests/readfile.o
DEPS=include/vector.h include/iterator.h include/DFP/ipv4.h include/DFP/domain.h include/DFP/hash.h
BUILD=build

TEST1=tests/benchmark_iterator.o 
TEST2=tests/benchmark_with_vectors.o 

all: create_build $(BUILD)/benchmark_iterator $(BUILD)/benchmark_with_vectors

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD)/benchmark_iterator: $(OBJ) $(TEST1)
	$(CC) -o $@ $^ $(CFLAGS)

$(BUILD)/benchmark_with_vectors: $(OBJ) $(TEST2)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

create_build:
	mkdir -p $(BUILD)

clean:
	rm -f src/*.o src/DFP/*.o build/benchmark_iterator build/benchmark_with_vectors
