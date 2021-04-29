all: tests

test_src := $(wildcard *.c)
tests: $(test_src:.c=.ll)
llvm_alias_res: $(test_src:.c=.llvm.res)
custom_alias_res: $(test_src:.c=.custom.res)
custom_inter_alias_res: $(test_src:.c=.custom.inter.res)

%.ll : %.c
	clang -Xclang -disable-O0-optnone -O0 -emit-llvm -S -c $<

%.llvm.res: %.ll
	opt -basic-aa -print-alias-sets -time-passes $< 2> $@

%.custom.res: %.ll
	opt -load ../bld/andersen.so --basic-aa-custom -print-pts-to-sets -time-passes $< 2> $@

%.custom.inter.res: %.ll
	opt -load ../bld/andersen.so --basic-aa-custom -print-pts-to-sets -interprocedural -time-passes $< 2> $@

clean: 
	rm -f *.ll *.bc *.llvm.res *.custom.res *.custom.inter.res

.PHONY: clean all tests llvm_alias_res alias_res
