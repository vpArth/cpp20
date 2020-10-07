CC=g++
CFLAGS=--std=c++20 -fcoroutines -Wall -O3

bin/main: main.cpp resumable.hpp handle.hpp
	mkdir -p bin
	$(CC) $(CFLAGS) $< -o $@

run: bin/main
	bin/main

clean:
	rm -rf bin/*
	rm -rf build/*
