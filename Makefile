all: andersen tests

andersen:
	@echo "Building Pass ..."
	make -C bld

tests:
	@echo "Compiling Tests ..."
	make -C tests

results: andersen tests
	@echo "Running Passes ..."
	make llvm_alias_res -C tests
	make custom_alias_res -C tests
	make custom_inter_alias_res -C tests

clean:
	make clean -C bld
	make clean -C tests

.PHONY: clean tests andersen results
