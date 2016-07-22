.PHONY: all test-all run-test-primes run-test-digits run-test-trie run-test-grid run-test-graph run-test-sets run-test-strings run-test-functional clean

all: clean test-all



test-all: run-test-primes run-test-trie run-test-grid run-test-graph run-test-sets run-test-strings run-test-functional

run-test-primes: test-primes
	@./test-primes --gtest_color=yes

run-test-digits: test-digits
	@./test-digits --gtest_color=yes

run-test-trie: test-trie
	@./test-trie --gtest_color=yes

run-test-grid: test-grid
	@./test-grid --gtest_color=yes

run-test-graph: test-graph
	@./test-graph --gtest_color=yes

run-test-sets: test-sets
	@./test-sets --gtest_color=yes

run-test-strings: test-strings
	@./test-strings --gtest_color=yes

run-test-functional: test-functional
	@./test-functional --gtest_color=yes

test-%: %.t.cpp %.h
	g++ -g -std=c++14 -pthread -I. -W -Wall -Wextra $< -L/usr/lib/ -lgtest_main -lgtest -lpthread -o $@

clean:
	rm -f test-primes test-digits test-trie test-grid test-graph test-set test-strings test-functional
	rm -rf test/outputs
