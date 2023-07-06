###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Dan Vaccaro


MAKEFLAGS += -L 

CXX      = g++
CXXFLAGS = -g3 -Wall -Wextra -std=c++14
LDFLAGS  = -g3

CalcYouLater : Datum.cpp DatumStack.cpp RPNCalc.cpp main.cpp
	${CXX} ${LDFLAGS} -o CalcYouLater Datum.cpp DatumStack.cpp RPNCalc.cpp main.cpp


##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^

clean:
	rm -rf CalcYouLater *.o *.dSYM
