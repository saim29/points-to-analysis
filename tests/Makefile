all: tests

test_src := $(wildcard *.c)
tests: $(test_src:.c=.ll)
llvm_alias_res: basic.llvm.res
custom_alias_res: basic.custom.res

%.ll : %.c
	clang -Xclang -disable-O0-optnone -O0 -emit-llvm -S -c $<

%.llvm.res: %.ll
	opt -basic-aa -print-alias-sets -time-passes $< 2> $@

%.custom.res: %.ll
	opt -load ../bld/andersen.so --basic-aa-custom -print-pts-to-sets -time-passes $< 2> $@

clean: 
	rm -f *.ll *.bc *.llvm.res *.custom.res

.PHONY: clean all tests llvm_alias_res alias_res
