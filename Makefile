CC=g++
CFLAGS=--std=c++20 -fcoroutines -Wall -O3

bin/main: main.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) $< -o $@

build: bin/main
run: bin/main
	bin/main
clean:
	rm -rf bin/*
	rm -rf build/*

.DEFAULT_GOAL := run
.PHONY: default run build clean
default: run
