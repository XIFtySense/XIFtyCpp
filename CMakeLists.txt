cmake_minimum_required(VERSION 3.20)
project(XIFtyCpp VERSION 0.1.0 DESCRIPTION "C++ binding for XIFty" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(DEFINED ENV{XIFTY_CORE_DIR})
  set(XIFTY_CORE_DIR "$ENV{XIFTY_CORE_DIR}")
else()
  set(XIFTY_CORE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.xifty-core")
endif()

message(STATUS "Using XIFty core from ${XIFTY_CORE_DIR}")

if(NOT EXISTS "${XIFTY_CORE_DIR}/.git")
  execute_process(
    COMMAND git clone --depth 1 --branch main https://github.com/XIFtySense/XIFty.git ${XIFTY_CORE_DIR}
    RESULT_VARIABLE XIFTY_CORE_CLONE_RESULT
  )
  if(NOT XIFTY_CORE_CLONE_RESULT EQUAL 0)
    message(FATAL_ERROR "failed to clone xifty core into ${XIFTY_CORE_DIR}")
  endif()
else()
  execute_process(
    COMMAND git -C ${XIFTY_CORE_DIR} fetch --depth 1 origin main
    RESULT_VARIABLE XIFTY_CORE_FETCH_RESULT
  )
  execute_process(
    COMMAND git -C ${XIFTY_CORE_DIR} checkout --force FETCH_HEAD
    RESULT_VARIABLE XIFTY_CORE_CHECKOUT_RESULT
  )
  if(NOT XIFTY_CORE_FETCH_RESULT EQUAL 0 OR NOT XIFTY_CORE_CHECKOUT_RESULT EQUAL 0)
    message(FATAL_ERROR "failed to refresh xifty core in ${XIFTY_CORE_DIR}")
  endif()
endif()

execute_process(
  COMMAND cargo build -p xifty-ffi --manifest-path ${XIFTY_CORE_DIR}/Cargo.toml
  RESULT_VARIABLE XIFTY_CORE_BUILD_RESULT
)

if(NOT XIFTY_CORE_BUILD_RESULT EQUAL 0)
  message(FATAL_ERROR "failed to build xifty-ffi from ${XIFTY_CORE_DIR}")
endif()

add_library(xifty_cpp src/xifty.cpp)
add_library(XIFty::xifty_cpp ALIAS xifty_cpp)
target_include_directories(xifty_cpp PUBLIC include)
target_include_directories(xifty_cpp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(xifty_cpp PRIVATE ${XIFTY_CORE_DIR}/target/debug/libxifty_ffi.a)

add_executable(xifty_cpp_example examples/basic_usage.cpp)
target_link_libraries(xifty_cpp_example PRIVATE xifty_cpp)
target_compile_definitions(xifty_cpp_example PRIVATE XIFTYCPP_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(xifty_cpp_gallery_example examples/gallery_ingest.cpp)
target_link_libraries(xifty_cpp_gallery_example PRIVATE xifty_cpp)
target_compile_definitions(xifty_cpp_gallery_example PRIVATE XIFTYCPP_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

enable_testing()
add_executable(xifty_cpp_tests tests/test_xifty.cpp)
target_link_libraries(xifty_cpp_tests PRIVATE xifty_cpp)
target_compile_definitions(xifty_cpp_tests PRIVATE XIFTYCPP_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
add_test(NAME xifty_cpp_tests COMMAND xifty_cpp_tests)
