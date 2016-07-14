.PHONY: all run-test clean

all: clean run-test trie-app

trie-app:
	g++ -O2 -I. -W -Wall -Wextra -std=c++14 ccct_trie.cpp -o trie-app

run-test: test
	@\time -p ./test --gtest_color=yes

test: ccct_trie.t.cpp
	g++ -O2 -I. -pthread -W -Wall -Wextra -std=c++14 ccct_trie.internal.t.cpp /usr/local/lib/libgtest.a -o test

clean: 
	rm -f test trie-app
	rm -rf test/outputs
