COMPILER = g++
FLAGS = -g -std=c++11 -Wall -Werror -Wextra

all:main

main: main.o
	$(COMPILER) $(FLAGS) main.o -o main

main.o: main.cpp btree.h
	$(COMPILER) $(FLAGS) -c main.cpp

clean:
	rm *.o *~ main
