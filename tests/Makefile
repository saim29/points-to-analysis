all: tests

tests: basic.ll
llvm_alias_res: basic.llvm.res
alias_res: basic.AA.res

%.ll : %.c
	clang -Xclang -disable-O0-optnone -O0 -emit-llvm -S -c $<

%.llvm.res: %.ll
	opt -basic-aa -print-alias-sets -time-passes $< 2> $@

%.AA.res: %ll

clean: 
	rm -f *.ll *.bc *.llvm.res

.PHONY: clean all tests llvm_alias_res alias_res
