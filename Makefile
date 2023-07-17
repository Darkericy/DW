# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/dakericy/DK_pratice/DW/CMakeFiles /home/dakericy/DK_pratice/DW//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/dakericy/DK_pratice/DW/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named DW

# Build rule for target.
DW: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 DW
.PHONY : DW

# fast build rule for target.
DW/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/build
.PHONY : DW/fast

#=============================================================================
# Target rules for targets named testlog

# Build rule for target.
testlog: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 testlog
.PHONY : testlog

# fast build rule for target.
testlog/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/testlog.dir/build.make CMakeFiles/testlog.dir/build
.PHONY : testlog/fast

#=============================================================================
# Target rules for targets named test_config

# Build rule for target.
test_config: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_config
.PHONY : test_config

# fast build rule for target.
test_config/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/build
.PHONY : test_config/fast

#=============================================================================
# Target rules for targets named test_thread

# Build rule for target.
test_thread: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_thread
.PHONY : test_thread

# fast build rule for target.
test_thread/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/build
.PHONY : test_thread/fast

DW/config.o: DW/config.cc.o
.PHONY : DW/config.o

# target to build an object file
DW/config.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/config.cc.o
.PHONY : DW/config.cc.o

DW/config.i: DW/config.cc.i
.PHONY : DW/config.i

# target to preprocess a source file
DW/config.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/config.cc.i
.PHONY : DW/config.cc.i

DW/config.s: DW/config.cc.s
.PHONY : DW/config.s

# target to generate assembly for a file
DW/config.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/config.cc.s
.PHONY : DW/config.cc.s

DW/log.o: DW/log.cc.o
.PHONY : DW/log.o

# target to build an object file
DW/log.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/log.cc.o
.PHONY : DW/log.cc.o

DW/log.i: DW/log.cc.i
.PHONY : DW/log.i

# target to preprocess a source file
DW/log.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/log.cc.i
.PHONY : DW/log.cc.i

DW/log.s: DW/log.cc.s
.PHONY : DW/log.s

# target to generate assembly for a file
DW/log.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/log.cc.s
.PHONY : DW/log.cc.s

DW/mutex.o: DW/mutex.cc.o
.PHONY : DW/mutex.o

# target to build an object file
DW/mutex.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/mutex.cc.o
.PHONY : DW/mutex.cc.o

DW/mutex.i: DW/mutex.cc.i
.PHONY : DW/mutex.i

# target to preprocess a source file
DW/mutex.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/mutex.cc.i
.PHONY : DW/mutex.cc.i

DW/mutex.s: DW/mutex.cc.s
.PHONY : DW/mutex.s

# target to generate assembly for a file
DW/mutex.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/mutex.cc.s
.PHONY : DW/mutex.cc.s

DW/thread.o: DW/thread.cc.o
.PHONY : DW/thread.o

# target to build an object file
DW/thread.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/thread.cc.o
.PHONY : DW/thread.cc.o

DW/thread.i: DW/thread.cc.i
.PHONY : DW/thread.i

# target to preprocess a source file
DW/thread.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/thread.cc.i
.PHONY : DW/thread.cc.i

DW/thread.s: DW/thread.cc.s
.PHONY : DW/thread.s

# target to generate assembly for a file
DW/thread.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/thread.cc.s
.PHONY : DW/thread.cc.s

DW/util.o: DW/util.cc.o
.PHONY : DW/util.o

# target to build an object file
DW/util.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/util.cc.o
.PHONY : DW/util.cc.o

DW/util.i: DW/util.cc.i
.PHONY : DW/util.i

# target to preprocess a source file
DW/util.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/util.cc.i
.PHONY : DW/util.cc.i

DW/util.s: DW/util.cc.s
.PHONY : DW/util.s

# target to generate assembly for a file
DW/util.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/util.cc.s
.PHONY : DW/util.cc.s

tests/test_config.o: tests/test_config.cc.o
.PHONY : tests/test_config.o

# target to build an object file
tests/test_config.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/tests/test_config.cc.o
.PHONY : tests/test_config.cc.o

tests/test_config.i: tests/test_config.cc.i
.PHONY : tests/test_config.i

# target to preprocess a source file
tests/test_config.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/tests/test_config.cc.i
.PHONY : tests/test_config.cc.i

tests/test_config.s: tests/test_config.cc.s
.PHONY : tests/test_config.s

# target to generate assembly for a file
tests/test_config.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/tests/test_config.cc.s
.PHONY : tests/test_config.cc.s

tests/test_thread.o: tests/test_thread.cc.o
.PHONY : tests/test_thread.o

# target to build an object file
tests/test_thread.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/tests/test_thread.cc.o
.PHONY : tests/test_thread.cc.o

tests/test_thread.i: tests/test_thread.cc.i
.PHONY : tests/test_thread.i

# target to preprocess a source file
tests/test_thread.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/tests/test_thread.cc.i
.PHONY : tests/test_thread.cc.i

tests/test_thread.s: tests/test_thread.cc.s
.PHONY : tests/test_thread.s

# target to generate assembly for a file
tests/test_thread.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/tests/test_thread.cc.s
.PHONY : tests/test_thread.cc.s

tests/testlog.o: tests/testlog.cc.o
.PHONY : tests/testlog.o

# target to build an object file
tests/testlog.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/testlog.dir/build.make CMakeFiles/testlog.dir/tests/testlog.cc.o
.PHONY : tests/testlog.cc.o

tests/testlog.i: tests/testlog.cc.i
.PHONY : tests/testlog.i

# target to preprocess a source file
tests/testlog.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/testlog.dir/build.make CMakeFiles/testlog.dir/tests/testlog.cc.i
.PHONY : tests/testlog.cc.i

tests/testlog.s: tests/testlog.cc.s
.PHONY : tests/testlog.s

# target to generate assembly for a file
tests/testlog.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/testlog.dir/build.make CMakeFiles/testlog.dir/tests/testlog.cc.s
.PHONY : tests/testlog.cc.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... DW"
	@echo "... test_config"
	@echo "... test_thread"
	@echo "... testlog"
	@echo "... DW/config.o"
	@echo "... DW/config.i"
	@echo "... DW/config.s"
	@echo "... DW/log.o"
	@echo "... DW/log.i"
	@echo "... DW/log.s"
	@echo "... DW/mutex.o"
	@echo "... DW/mutex.i"
	@echo "... DW/mutex.s"
	@echo "... DW/thread.o"
	@echo "... DW/thread.i"
	@echo "... DW/thread.s"
	@echo "... DW/util.o"
	@echo "... DW/util.i"
	@echo "... DW/util.s"
	@echo "... tests/test_config.o"
	@echo "... tests/test_config.i"
	@echo "... tests/test_config.s"
	@echo "... tests/test_thread.o"
	@echo "... tests/test_thread.i"
	@echo "... tests/test_thread.s"
	@echo "... tests/testlog.o"
	@echo "... tests/testlog.i"
	@echo "... tests/testlog.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

