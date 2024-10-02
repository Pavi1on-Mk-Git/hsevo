BROWSER = powershell.exe

.DEFAULT_GOAL := all

.PHONY: test

run:
	@ ./build/bin/hsevo

debug:
	@ gdb ./build/bin/hsevo

test:
	@ ./build/bin/test_hsevo

debug_test:
	@ gdb ./build/bin/test_hsevo

coverage:
	@ ./build/bin/test_hsevo
	@ lcov -q -no-external -d ./src -d ./include -d ./build/CMakeFiles/test_hsevo.dir -c -o ./build/bin/test_coverage.info 2> /dev/null
	@ genhtml -q ./build/bin/test_coverage.info --output-directory ./build/bin/coverage 2> /dev/null
	@ $(BROWSER) ./build/bin/coverage/index.html

profile:
	@ mkdir -p ./build/bin/profiling
	@ valgrind --callgrind-out-file="./build/bin/profiling/profile.out" --tool=callgrind ./build/bin/hsevo
	@ kcachegrind ./build/bin/profiling/profile.out

%:
	@$(MAKE) --no-print-directory -C build $@
