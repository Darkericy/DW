cmake_minimum_required(VERSION 3.0)
project(DW)

link_directories("/home/dakericy/yaml/yaml-cpp-master/include")

include (cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
# set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O3 -g -std=c++14")
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c++17 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")

set(
    LIB_SRC
    DW/config.cc
    DW/util.cc
    DW/log.cc
    DW/thread.cc
    DW/mutex.cc
    DW/fiber.cc
    DW/scheduler.cc
    DW/iomanager.cc
    DW/timer.cc
    DW/hook.cc
    DW/fd_manager.cc
    DW/address.cc
)

add_library(DW SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(DW)
# add_library(DW_static STATIC ${LIB_SRC})
# SET_TARGET_PROPERTIES (DW_static PROPERTIES OUTPUT_NAME "DW")

add_executable(testlog tests/testlog.cc)
add_dependencies(testlog DW)
force_redefine_file_macro_for_sources(testlog)
target_link_libraries(testlog DW yaml-cpp)

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config DW)
force_redefine_file_macro_for_sources(test_config)
target_link_libraries(test_config DW yaml-cpp)

add_executable(test_thread tests/test_thread.cc)
add_dependencies(test_thread DW)
force_redefine_file_macro_for_sources(test_thread)
target_link_libraries(test_thread DW yaml-cpp)

add_executable(test_util tests/test_util.cc)
add_dependencies(test_util DW)
force_redefine_file_macro_for_sources(test_util)
target_link_libraries(test_util DW yaml-cpp)

add_executable(test_fiber tests/test_fiber.cc)
add_dependencies(test_fiber DW)
force_redefine_file_macro_for_sources(test_fiber)
target_link_libraries(test_fiber DW yaml-cpp)

add_executable(test_scheduler tests/test_scheduler.cc)
add_dependencies(test_scheduler DW)
force_redefine_file_macro_for_sources(test_scheduler)
target_link_libraries(test_scheduler DW yaml-cpp)

add_executable(test_iomanager tests/test_iomanager.cc)
add_dependencies(test_iomanager DW)
force_redefine_file_macro_for_sources(test_iomanager)
target_link_libraries(test_iomanager DW yaml-cpp)

add_executable(test_hook tests/test_hook.cc)
add_dependencies(test_hook DW)
force_redefine_file_macro_for_sources(test_hook)
target_link_libraries(test_hook DW yaml-cpp)

add_executable(test_address tests/test_address.cc)
add_dependencies(test_address DW)
force_redefine_file_macro_for_sources(test_address)
target_link_libraries(test_address DW yaml-cpp)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)