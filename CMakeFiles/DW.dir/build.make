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
include CMakeFiles/DW.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DW.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DW.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DW.dir/flags.make

CMakeFiles/DW.dir/DW/log.cc.o: CMakeFiles/DW.dir/flags.make
CMakeFiles/DW.dir/DW/log.cc.o: DW/log.cc
CMakeFiles/DW.dir/DW/log.cc.o: CMakeFiles/DW.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dakericy/DK_pratice/DW/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DW.dir/DW/log.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DW.dir/DW/log.cc.o -MF CMakeFiles/DW.dir/DW/log.cc.o.d -o CMakeFiles/DW.dir/DW/log.cc.o -c /home/dakericy/DK_pratice/DW/DW/log.cc

CMakeFiles/DW.dir/DW/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DW.dir/DW/log.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dakericy/DK_pratice/DW/DW/log.cc > CMakeFiles/DW.dir/DW/log.cc.i

CMakeFiles/DW.dir/DW/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DW.dir/DW/log.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dakericy/DK_pratice/DW/DW/log.cc -o CMakeFiles/DW.dir/DW/log.cc.s

# Object files for target DW
DW_OBJECTS = \
"CMakeFiles/DW.dir/DW/log.cc.o"

# External object files for target DW
DW_EXTERNAL_OBJECTS =

lib/libDW.so: CMakeFiles/DW.dir/DW/log.cc.o
lib/libDW.so: CMakeFiles/DW.dir/build.make
lib/libDW.so: CMakeFiles/DW.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dakericy/DK_pratice/DW/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library lib/libDW.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DW.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DW.dir/build: lib/libDW.so
.PHONY : CMakeFiles/DW.dir/build

CMakeFiles/DW.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DW.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DW.dir/clean

CMakeFiles/DW.dir/depend:
	cd /home/dakericy/DK_pratice/DW && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dakericy/DK_pratice/DW /home/dakericy/DK_pratice/DW /home/dakericy/DK_pratice/DW /home/dakericy/DK_pratice/DW /home/dakericy/DK_pratice/DW/CMakeFiles/DW.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DW.dir/depend

