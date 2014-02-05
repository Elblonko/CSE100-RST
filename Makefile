# A simple makefile for CSE 100 P1

#use g++ for everything
CC= g++  	

# include debugging symbols in object files,
# and enable all warnings
CXXFLAGS= -std=c++11 -g -Wall

#include debugging symbols in executable
LDFLAGS= -g	

benchtree: benchtree.o countint.o
	g++ -o benchtree -g benchtree.o countint.o

countint.o: countint.hpp

benchtree.o: BST.hpp BSTNode.hpp BSTIterator.hpp RST.hpp

#compile code for test_BSTRST.cpp
test_BSTRST: test_BSTRST.o
	g++ -o test_BSTRST -g test_BSTRST.o

test_BSTRST.o: BST.hpp BSTNode.hpp BSTIterator.hpp RST.hpp

#compile code for test_RST.cpp
test_RST: test_RST.o countint.o
	g++ -o test_RST -g test_RST.o countint.o

countint.o: countint.hpp

test_RST.o: BST.hpp BSTNode.hpp BSTIterator.hpp RST.hpp

#comple code for test_leak
leaktest_RST: leaktest_RST.o
	g++ -o leaktest -g leaktest_RST.o countint.o

countint.o: countint.hpp

leaktest_RST.o: BST.hpp BSTNode.hpp BSTIterator.hpp RST.hpp
