.PHONY: test
test: a.out
	@./.run_tests.sh

a.out: main.cpp
	g++ -W -Wall -Wextra -Wpedantic -std=c++11 main.cpp

.PHONY: clean
clean: 
	rm -f a.out
	rm -rf test/outputs
