#
# Makefile for Heap Lab
#
CXX      = clang++
CXXFLAGS = -Wall -Wextra -Wreturn-type -g
LDFLAGS  = -g

heapSort: main.o heap.o
	${CXX} ${CXXFLAGS} -o heapSort main.o heap.o

main.o:  main.cpp heap.h
heap.o:  heap.cpp heap.h

clean:
	rm -rf heapSort *.o *.dSYM