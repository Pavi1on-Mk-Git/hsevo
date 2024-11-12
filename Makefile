BROWSER = powershell.exe

.DEFAULT_GOAL := all

.PHONY: test

run:
	@ ./build/bin/hsevo

debug:
	@ gdb ./build/bin/hsevo

experiment:
	@ ./build/bin/experiment_hsevo

gui:
	@ ./build/bin/gui_hsevo

debug_gui:
	@ gdb ./build/bin/gui_hsevo

test:
	@ ./build/bin/test_hsevo

debug_test:
	@ gdb ./build/bin/test_hsevo

coverage:
	@ ./build/bin/test_hsevo
	@ lcov -q -no-external -d ./src -d ./include -d ./build/CMakeFiles/test_hsevo.dir -c --ignore-errors empty -o ./build/bin/test_coverage.info 2> /dev/null
	@ genhtml -q ./build/bin/test_coverage.info --output-directory ./build/bin/coverage 2> /dev/null
	@ $(BROWSER) ./build/bin/coverage/index.html

profile:
	@ $(MAKE) -j$$(nproc) --no-print-directory -C build profile_hsevo
	@ mkdir -p ./build/bin/profiling
	@ ./build/bin/profile_hsevo
	@ mv ./gmon.out ./build/bin/profiling
	@ gprof ./build/bin/profile_hsevo ./build/bin/profiling/gmon.out > ./build/bin/profiling/hsevo_analysis.txt

zip:
	@ zip -r ./code_archives/HSEVO_$$(date '+%d.%m.%Y').zip ./include ./src ./test ./.clang-format ./CMakeLists.txt ./Makefile

%:
	@ $(MAKE) -j$$(nproc) --no-print-directory -C build $@
