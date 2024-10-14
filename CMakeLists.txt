cmake_minimum_required(VERSION 3.22)
project(hsevo)

include_directories(include)

set(COMMON_FLAGS -std=c++20 -Wall -Werror -Wextra -Wpedantic)
set(DEBUG_FLAGS ${COMMON_FLAGS} -Og -g)
set(OPTIMIZED_FLAGS ${COMMON_FLAGS} -O3)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE AI_SOURCES CONFIGURE_DEPENDS "src/ai/*.cc")
file(GLOB_RECURSE GUI_SOURCES CONFIGURE_DEPENDS "src/gui/*.cc")
file(GLOB_RECURSE LOGIC_SOURCES CONFIGURE_DEPENDS "src/logic/*.cc")
file(GLOB_RECURSE PLAYERS_SOURCES CONFIGURE_DEPENDS "src/players/*.cc")
file(GLOB_RECURSE UTILS_SOURCES CONFIGURE_DEPENDS "src/utils/*.cc")

add_executable(hsevo ${AI_SOURCES} ${LOGIC_SOURCES} ${PLAYERS_SOURCES} ${UTILS_SOURCES} "src/main.cc")
target_compile_options(hsevo PRIVATE ${DEBUG_FLAGS} -DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)

add_executable(experiment_hsevo ${AI_SOURCES} ${LOGIC_SOURCES} ${PLAYERS_SOURCES} ${UTILS_SOURCES} "src/run_experiment.cc")
target_compile_options(experiment_hsevo PRIVATE ${OPTIMIZED_FLAGS} -DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_OFF)

add_executable(gui_hsevo ${AI_SOURCES} ${GUI_SOURCES} ${LOGIC_SOURCES} ${PLAYERS_SOURCES} ${UTILS_SOURCES} "src/gui.cc")
target_compile_options(gui_hsevo PRIVATE ${DEBUG_FLAGS} -DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "test/*.cc" "src/*.cc")
list(FILTER TEST_SOURCES EXCLUDE REGEX "src/main.cc")

add_executable(test_hsevo ${TEST_SOURCES})
target_compile_options(test_hsevo PRIVATE ${DEBUG_FLAGS} --coverage -DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_OFF)
target_link_options(test_hsevo PRIVATE --coverage)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.3
)
FetchContent_MakeAvailable(Catch2)

target_link_libraries(test_hsevo PRIVATE Catch2::Catch2WithMain)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG        v1.14.1
)
FetchContent_MakeAvailable(spdlog)

target_link_libraries(hsevo PRIVATE spdlog::spdlog)
target_link_libraries(experiment_hsevo PRIVATE spdlog::spdlog)
target_link_libraries(gui_hsevo PRIVATE spdlog::spdlog)
target_link_libraries(test_hsevo PRIVATE spdlog::spdlog)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        5.0
  GIT_SHALLOW    1
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
  raylib_cpp
  GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
  GIT_TAG        v5.0.2
)
FetchContent_MakeAvailable(raylib_cpp)

target_link_libraries(gui_hsevo PRIVATE raylib raylib_cpp)

find_package(Boost 1.83 REQUIRED serialization)
target_link_libraries(hsevo PRIVATE Boost::serialization)
target_link_libraries(experiment_hsevo PRIVATE Boost::serialization)
target_link_libraries(gui_hsevo PRIVATE Boost::serialization)
target_link_libraries(test_hsevo PRIVATE Boost::serialization)
