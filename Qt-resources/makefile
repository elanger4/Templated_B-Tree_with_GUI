COMPILER = clang++
FLAGS =  -g -std=c++11 -Wall -Werror -Wextra -pedantic

all:main

main: erik.cpp btree.h bnode.h
	$(COMPILER) $(FLAGS) erik.cpp -o main


#main: main.o
#	$(COMPILER) $(FLAGS) main.o -o main

#main.o: main.cpp btree.h node.h
#	$(COMPILER) $(FLAGS) -c main.cpp

clean:
	rm -f *.o *~ main


