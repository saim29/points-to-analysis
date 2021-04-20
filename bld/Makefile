INC=-I/usr/local/include/
all: andersen.so

CXXFLAGS = -rdynamic $(shell llvm-config --cxxflags) $(INC) -g -O0 -fPIC
VPATH = ../src ../include

andersen.o: andersen.cpp andersen.h

%.so: %.o 
	$(CXX) -dylib -shared $^ -o $@

clean:
	rm -f *.o *.so

.PHONY: clean all
