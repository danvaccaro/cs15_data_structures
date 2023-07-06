# Comp 15: Data Structures
# Tufts University
# Makefile for Lab 1

CXX      = clang++

# these two flags will not provide memory leak/error checking.
CXXFLAGS = -std=c++11 -Wall -Wextra -g3 -c
LDFLAGS  = -g3 

# use these to have memory leak/error checking
# before running `make`, ensure that the path to the llvm-symbolizer is in your $PATH
# see the lab doc for details
# CXXFLAGS = -Wall -Wextra -g3 -fsanitize=address -fno-omit-frame-pointer
# LDFLAGS  = -g3 -fsanitize=address

shop: main.o ArrayList.o
	$(CXX) $(LDFLAGS) -o shop main.o ArrayList.o 

main.o: main.cpp ArrayList.h
	$(CXX) $(CXXFLAGS) main.cpp

ArrayList.o: ArrayList.cpp ArrayList.h
	$(CXX) $(CXXFLAGS) ArrayList.cpp
	
clean:
	rm -f *.o core* *~ shop
