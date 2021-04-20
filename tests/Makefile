all: basic.ll

%.ll : %.c
	clang -Xclang -disable-O0-optnone -O0 -emit-llvm -S -c $<

clean: 
	rm -f *.ll *.bc

.PHONY: clean all
