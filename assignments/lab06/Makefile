#
# Makefile for BSTree
#
CXX      = clang++
CXXFLAGS = -Wall -Wextra -Wconversion -Wreturn-type -g
LDFLAGS  = -g

tree_traversal: main.o BSTree.o
	${CXX} ${LDFLAGS} -o tree_traversal  main.o BSTree.o

main.o:    main.cpp BSTree.h
BSTree.o:  BSTree.cpp BSTree.h

clean:
	rm -rf tree_traversal *.o *~ *.dSYM
