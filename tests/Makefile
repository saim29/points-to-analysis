all: basic.bc basic.ll

%.bc : %.c
	clang -Xclang -disable-O0-optnone -O0 -emit-llvm -c $<

%.ll : %.bc
	llvm-dis $<
clean: 
	rm -f *.ll *.bc

.PHONY: clean all
