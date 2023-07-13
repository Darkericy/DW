cmake_minimum_required(VERSION 3.0)

project(DW)

set(CMAKE_VERBOSE_MAKEFILE ON)
# set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O3 -g -std=c++14")
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c++14 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")

set(
    LIB_SRC
    DW/log.cc
)

add_library(DW SHARED ${LIB_SRC})
# add_library(DW_static STATIC ${LIB_SRC})
# SET_TARGET_PROPERTIES (DW_static PROPERTIES OUTPUT_NAME "DW")

add_executable(testlog tests/testlog.cc)
add_dependencies(testlog DW)
target_link_libraries(testlog DW)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)