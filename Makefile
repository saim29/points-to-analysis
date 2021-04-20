all: andersen tests

andersen:
	@echo "Building Pass ..."
	make -C bld

tests:

clean:
	make clean -C bld

.PHONY: clean tests andersen
