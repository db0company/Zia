##
## Makefile for zia
## by lenorm_f
##

_comma = ,

NAME = api_test

TESTS = \
	irequest

TESTS_SRC = $(addsuffix _test.cpp,$(TESTS))
TESTS_OBJ = $(TESTS_SRC:.cpp=.o)
TESTS_FUNCTIONS = $(addsuffix $(_comma),$(addprefix \&,$(addsuffix _test, $(TESTS))))
TESTS_PROTOS = $(addprefix int ,$(addsuffix _test();,$(TESTS)))

CXXFLAGS = -I.. -Wall -Wextra -std=c++0x

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.cpp:
	$(shell echo "#! /usr/bin/env bash" > main.cpp.bash)
	$(shell for i in "$(TESTS_PROTOS)"; do echo "echo \"$$i\"" >> main.cpp.bash; done)
	$(shell while read l; do echo "echo \"$$(echo $$l | sed 's/\"/\\\"/g')\"" >> main.cpp.bash; done < main.cpp.template)
	$(shell TESTS=$(TESTS_FUNCTIONS) bash main.cpp.bash > main.cpp)

$(NAME): $(TESTS_OBJ)
	$(CXX) main.o $(TESTS_OBJ) -o $(NAME)

all: main.cpp main.o $(NAME)

clean:
	rm -f $(TESTS_OBJ) main.o

distclean: clean
	rm -f $(NAME) main.cpp main.cpp.bash

re: distclean all
