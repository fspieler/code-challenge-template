.PHONY: all test-all run-test-primes run-test-trie clean

all: clean test-all

test-all: run-test-primes run-test-trie run-test-graph

run-test-primes: test-primes
	@./test-primes --gtest_color=yes

run-test-trie: test-trie
	@./test-trie --gtest_color=yes

run-test-graph: test-graph
	@./test-graph --gtest_color=yes

test-%: %.t.cpp
	g++ -g -std=c++14 -pthread -I. -W -Wall -Wextra $< -L/usr/lib/ -lgtest_main -lgtest -lpthread -o $@

clean:
	rm -f test-primes test-trie test-graph
	rm -rf test/outputs
