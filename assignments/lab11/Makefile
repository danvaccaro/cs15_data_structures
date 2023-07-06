#
# Makefile for Sorting
#
# New compiler flags:
#
# -On is the optimization flag ('O' stands for 'Optimization', not
#     Big-O, but wouldn't that be amazing!).
# -Og means to optimize with a good        <= For debugging
#     debugging experience in mind
# -O0 means do very little optimzation     <= The default
#     sometimes good when debugging
# -O1 means to do 'usual' optimizations.   <= Usually a good tradeoff
# -O2 means to do extra optimizations that <= Common for commercial products
#     make compilatio slower but usually
#     lead to better performance. 
# -O3 means to go nuts and try more        <= Use at your own risk
#     experimental optimizations that are
#     not always guaranteed to be correct.
#
# Linker flag:
# -s  is a GNU (g++) linker flag that means to strip 'symbol table'
#     information from the binary.  It is also supported by clang++ on
#     our servers, but I think it is deprecated in later clang-based
#     systems.
#     It makes debugging harder and definitely make the executable
#     file smaller.  I doubt it helps performance, but I put it in
#     anyway.
#
#
# 
CXX      = clang++
CXXFLAGS = -Wall -Wextra -Wreturn-type -std=c++11 -g
LDFLAGS  = -g 

sort: sorting.o
	${CXX} ${CXXFLAGS} -o sort sorting.o

sorting.o: sorting.cpp

faster:  sorting.cpp
	${CXX} -Wall -Wextra -std=c++11 -O2 -s -o $@ $<

fastest:  sorting.cpp
	${CXX} -Wall -Wextra -std=c++11 -O3 -s -o $@ $<

clean:
	rm -rf sort *.o *.dSYM *~