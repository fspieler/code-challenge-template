.PHONY: test
test: a.out
	@./.run_tests

a.out: main.cpp
	g++ -O2 -I. -Ichallenge_lib -W -Wall -Wextra -std=c++14 main.cpp

.PHONY: clean
clean: 
	rm -f a.out
	rm -rf test/outputs
