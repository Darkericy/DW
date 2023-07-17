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
    DW/singleton.h
    DW/util.cc
    DW/log.cc
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

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)