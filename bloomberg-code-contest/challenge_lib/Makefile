.PHONY: all test clean

all: clean test

test: test-suite
	@\time -p ./test-suite

test-suite: trie.t.cpp
	g++ -O2 -std=c++14 -pthread -I. -W -Wall -Wextra primes.t.cpp -lgtest_main -lgtest -lpthread -o test-suite

clean: 
	rm -f a.out
	rm -rf test/outputs
