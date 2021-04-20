INC=-I/usr/local/include/
all: andersen.so

CXXFLAGS = -rdynamic $(shell llvm-config --cxxflags) $(INC) -g -O0 -fPIC
VPATH = ../src ../include

constraintGraph.o: constraintGraph.cpp constraintGraph.h
constraintCollector.o: constraintCollector.cpp constraintCollector.h

%.so: %.o constraintGraph.o 
	$(CXX) -dylib -shared $^ -o $@

clean:
	rm -f *.o *.so

.PHONY: clean all
