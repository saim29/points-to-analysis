all: andersen tests

andersen:
	@echo "Building Pass ..."
	make -C bld

tests:
	@echo "Compiling Tests ..."
	make -C tests

clean:
	make clean -C bld
	make clean -C tests

.PHONY: clean tests andersen
