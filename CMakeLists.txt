cmake_minimum_required(VERSION 3.20)
project(XIFtyCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(DEFINED ENV{XIFTY_CORE_DIR})
  set(XIFTY_CORE_DIR "$ENV{XIFTY_CORE_DIR}")
else()
  set(XIFTY_CORE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../XIFty")
endif()

execute_process(
  COMMAND cargo build -p xifty-ffi --manifest-path ${XIFTY_CORE_DIR}/Cargo.toml
  RESULT_VARIABLE XIFTY_CORE_BUILD_RESULT
)

if(NOT XIFTY_CORE_BUILD_RESULT EQUAL 0)
  message(FATAL_ERROR "failed to build xifty-ffi from ${XIFTY_CORE_DIR}")
endif()

add_library(xifty_cpp src/xifty.cpp)
target_include_directories(xifty_cpp PUBLIC include)
target_include_directories(xifty_cpp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(xifty_cpp PRIVATE ${XIFTY_CORE_DIR}/target/debug/libxifty_ffi.a)

add_executable(xifty_cpp_example examples/basic_usage.cpp)
target_link_libraries(xifty_cpp_example PRIVATE xifty_cpp)
target_compile_definitions(xifty_cpp_example PRIVATE XIFTYCPP_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

enable_testing()
add_executable(xifty_cpp_tests tests/test_xifty.cpp)
target_link_libraries(xifty_cpp_tests PRIVATE xifty_cpp)
target_compile_definitions(xifty_cpp_tests PRIVATE XIFTYCPP_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
add_test(NAME xifty_cpp_tests COMMAND xifty_cpp_tests)
