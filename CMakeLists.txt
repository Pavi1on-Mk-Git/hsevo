cmake_minimum_required(VERSION 3.22)
project(hsevo)

include_directories(include)

set(COMMON_FLAGS -std=c++17 -Og -g -Wall -Werror -Wextra -Wpedantic)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cc")

add_executable(hsevo ${SOURCES})
target_compile_options(hsevo PRIVATE ${COMMON_FLAGS} -DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "test/*.cc" "src/*.cc")
list(FILTER TEST_SOURCES EXCLUDE REGEX "src/main.cc")

add_executable(test_hsevo ${TEST_SOURCES})
target_compile_options(test_hsevo PRIVATE ${COMMON_FLAGS} --coverage -DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_OFF)
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
target_link_libraries(test_hsevo PRIVATE spdlog::spdlog)
