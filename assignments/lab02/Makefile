#
#  Comp 15: Data Structures
#  Tufts University
#  Makefile for Lab 2
#
#  Makefile for planet-driver, LinkedList and Planet
#

CXX      = clang++
CXXFLAGS = -Wall -Wextra -g
LDFlagS  = -g


planet-driver: planet-driver.o Planet.o LinkedList.o
	$(CXX) $(LDFlagS) -o planet-driver planet-driver.o Planet.o LinkedList.o

LinkedList_tests.o: LinkedList_tests.cpp LinkedList.h Planet.h
	$(CXX) $(CXXFLAGS) -c LinkedList_tests.cpp
	
#
# Only listing dependencies here
# make has a default rule that knows how to build a .o
# file from a .cpp file using $(CXX) and $(CXXFLAGS)
#
planet-driver.o: planet-driver.cpp LinkedList.h
	$(CXX) $(CXXFLAGS) -c planet-driver.cpp

LinkedList.o: LinkedList.cpp LinkedList.h Planet.h
	$(CXX) $(CXXFLAGS) -c LinkedList.cpp
	
Planet.o: Planet.cpp Planet.h
	$(CXX) $(CXXFLAGS) -c Planet.cpp


clean:
	rm -f *.o core* *~ planet-driver
