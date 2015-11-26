.PHONY: all test clean

all: clean test

test: a.out
	@\time -p ./a.out

a.out: ccct_trie.t.cpp
	g++ -O2 -I. -W -Wall -Wextra -std=c++14 ccct_trie.t.cpp

clean: 
	rm -f a.out
	rm -rf test/outputs
