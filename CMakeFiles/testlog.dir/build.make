# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dakericy/DK_pratice/DW

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dakericy/DK_pratice/DW

# Include any dependencies generated for this target.
include CMakeFiles/testlog.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/testlog.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/testlog.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testlog.dir/flags.make

CMakeFiles/testlog.dir/tests/testlog.cc.o: CMakeFiles/testlog.dir/flags.make
CMakeFiles/testlog.dir/tests/testlog.cc.o: tests/testlog.cc
CMakeFiles/testlog.dir/tests/testlog.cc.o: CMakeFiles/testlog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dakericy/DK_pratice/DW/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testlog.dir/tests/testlog.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testlog.dir/tests/testlog.cc.o -MF CMakeFiles/testlog.dir/tests/testlog.cc.o.d -o CMakeFiles/testlog.dir/tests/testlog.cc.o -c /home/dakericy/DK_pratice/DW/tests/testlog.cc

CMakeFiles/testlog.dir/tests/testlog.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testlog.dir/tests/testlog.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dakericy/DK_pratice/DW/tests/testlog.cc > CMakeFiles/testlog.dir/tests/testlog.cc.i

CMakeFiles/testlog.dir/tests/testlog.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testlog.dir/tests/testlog.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dakericy/DK_pratice/DW/tests/testlog.cc -o CMakeFiles/testlog.dir/tests/testlog.cc.s

# Object files for target testlog
testlog_OBJECTS = \
"CMakeFiles/testlog.dir/tests/testlog.cc.o"

# External object files for target testlog
testlog_EXTERNAL_OBJECTS =

bin/testlog: CMakeFiles/testlog.dir/tests/testlog.cc.o
bin/testlog: CMakeFiles/testlog.dir/build.make
bin/testlog: lib/libDW.so
bin/testlog: CMakeFiles/testlog.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dakericy/DK_pratice/DW/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/testlog"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testlog.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testlog.dir/build: bin/testlog
.PHONY : CMakeFiles/testlog.dir/build

CMakeFiles/testlog.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testlog.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testlog.dir/clean

CMakeFiles/testlog.dir/depend:
	cd /home/dakericy/DK_pratice/DW && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dakericy/DK_pratice/DW /home/dakericy/DK_pratice/DW /home/dakericy/DK_pratice/DW /home/dakericy/DK_pratice/DW /home/dakericy/DK_pratice/DW/CMakeFiles/testlog.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testlog.dir/depend
