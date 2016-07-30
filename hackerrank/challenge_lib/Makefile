# add header to targets
targets=$(shell cat headers_list)
.PHONY: all test-all clean
all: clean test-all

define TEST_template =
.PHONY: run-test-$(1) clean-$(1)
test-all: run-test-$(1)
run-test-$(1): test-$(1)
	@./test-$(1) --gtest_color=yes
clean: clean-$(1)
clean-$(1):
	rm -f test-$(1)
endef

$(foreach test,$(targets),$(eval $(call TEST_template,$(test))))

test-%: %.t.cpp %.h
	g++ -g -std=c++14 -pthread -I. -W -Wall -Wextra $< -L/usr/lib/ -lgtest_main -lgtest -lpthread -o $@
