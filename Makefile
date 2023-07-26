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

#=============================================================================
# Target rules for targets named test_util

# Build rule for target.
test_util: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_util
.PHONY : test_util

# fast build rule for target.
test_util/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/build
.PHONY : test_util/fast

#=============================================================================
# Target rules for targets named test_fiber

# Build rule for target.
test_fiber: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_fiber
.PHONY : test_fiber

# fast build rule for target.
test_fiber/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_fiber.dir/build.make CMakeFiles/test_fiber.dir/build
.PHONY : test_fiber/fast

#=============================================================================
# Target rules for targets named test_scheduler

# Build rule for target.
test_scheduler: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_scheduler
.PHONY : test_scheduler

# fast build rule for target.
test_scheduler/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_scheduler.dir/build.make CMakeFiles/test_scheduler.dir/build
.PHONY : test_scheduler/fast

#=============================================================================
# Target rules for targets named test_iomanager

# Build rule for target.
test_iomanager: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_iomanager
.PHONY : test_iomanager

# fast build rule for target.
test_iomanager/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_iomanager.dir/build.make CMakeFiles/test_iomanager.dir/build
.PHONY : test_iomanager/fast

#=============================================================================
# Target rules for targets named test_hook

# Build rule for target.
test_hook: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_hook
.PHONY : test_hook

# fast build rule for target.
test_hook/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_hook.dir/build.make CMakeFiles/test_hook.dir/build
.PHONY : test_hook/fast

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

DW/fd_manager.o: DW/fd_manager.cc.o
.PHONY : DW/fd_manager.o

# target to build an object file
DW/fd_manager.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/fd_manager.cc.o
.PHONY : DW/fd_manager.cc.o

DW/fd_manager.i: DW/fd_manager.cc.i
.PHONY : DW/fd_manager.i

# target to preprocess a source file
DW/fd_manager.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/fd_manager.cc.i
.PHONY : DW/fd_manager.cc.i

DW/fd_manager.s: DW/fd_manager.cc.s
.PHONY : DW/fd_manager.s

# target to generate assembly for a file
DW/fd_manager.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/fd_manager.cc.s
.PHONY : DW/fd_manager.cc.s

DW/fiber.o: DW/fiber.cc.o
.PHONY : DW/fiber.o

# target to build an object file
DW/fiber.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/fiber.cc.o
.PHONY : DW/fiber.cc.o

DW/fiber.i: DW/fiber.cc.i
.PHONY : DW/fiber.i

# target to preprocess a source file
DW/fiber.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/fiber.cc.i
.PHONY : DW/fiber.cc.i

DW/fiber.s: DW/fiber.cc.s
.PHONY : DW/fiber.s

# target to generate assembly for a file
DW/fiber.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/fiber.cc.s
.PHONY : DW/fiber.cc.s

DW/hook.o: DW/hook.cc.o
.PHONY : DW/hook.o

# target to build an object file
DW/hook.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/hook.cc.o
.PHONY : DW/hook.cc.o

DW/hook.i: DW/hook.cc.i
.PHONY : DW/hook.i

# target to preprocess a source file
DW/hook.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/hook.cc.i
.PHONY : DW/hook.cc.i

DW/hook.s: DW/hook.cc.s
.PHONY : DW/hook.s

# target to generate assembly for a file
DW/hook.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/hook.cc.s
.PHONY : DW/hook.cc.s

DW/iomanager.o: DW/iomanager.cc.o
.PHONY : DW/iomanager.o

# target to build an object file
DW/iomanager.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/iomanager.cc.o
.PHONY : DW/iomanager.cc.o

DW/iomanager.i: DW/iomanager.cc.i
.PHONY : DW/iomanager.i

# target to preprocess a source file
DW/iomanager.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/iomanager.cc.i
.PHONY : DW/iomanager.cc.i

DW/iomanager.s: DW/iomanager.cc.s
.PHONY : DW/iomanager.s

# target to generate assembly for a file
DW/iomanager.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/iomanager.cc.s
.PHONY : DW/iomanager.cc.s

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

DW/scheduler.o: DW/scheduler.cc.o
.PHONY : DW/scheduler.o

# target to build an object file
DW/scheduler.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/scheduler.cc.o
.PHONY : DW/scheduler.cc.o

DW/scheduler.i: DW/scheduler.cc.i
.PHONY : DW/scheduler.i

# target to preprocess a source file
DW/scheduler.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/scheduler.cc.i
.PHONY : DW/scheduler.cc.i

DW/scheduler.s: DW/scheduler.cc.s
.PHONY : DW/scheduler.s

# target to generate assembly for a file
DW/scheduler.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/scheduler.cc.s
.PHONY : DW/scheduler.cc.s

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

DW/timer.o: DW/timer.cc.o
.PHONY : DW/timer.o

# target to build an object file
DW/timer.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/timer.cc.o
.PHONY : DW/timer.cc.o

DW/timer.i: DW/timer.cc.i
.PHONY : DW/timer.i

# target to preprocess a source file
DW/timer.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/timer.cc.i
.PHONY : DW/timer.cc.i

DW/timer.s: DW/timer.cc.s
.PHONY : DW/timer.s

# target to generate assembly for a file
DW/timer.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DW.dir/build.make CMakeFiles/DW.dir/DW/timer.cc.s
.PHONY : DW/timer.cc.s

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

tests/test_fiber.o: tests/test_fiber.cc.o
.PHONY : tests/test_fiber.o

# target to build an object file
tests/test_fiber.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_fiber.dir/build.make CMakeFiles/test_fiber.dir/tests/test_fiber.cc.o
.PHONY : tests/test_fiber.cc.o

tests/test_fiber.i: tests/test_fiber.cc.i
.PHONY : tests/test_fiber.i

# target to preprocess a source file
tests/test_fiber.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_fiber.dir/build.make CMakeFiles/test_fiber.dir/tests/test_fiber.cc.i
.PHONY : tests/test_fiber.cc.i

tests/test_fiber.s: tests/test_fiber.cc.s
.PHONY : tests/test_fiber.s

# target to generate assembly for a file
tests/test_fiber.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_fiber.dir/build.make CMakeFiles/test_fiber.dir/tests/test_fiber.cc.s
.PHONY : tests/test_fiber.cc.s

tests/test_hook.o: tests/test_hook.cc.o
.PHONY : tests/test_hook.o

# target to build an object file
tests/test_hook.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_hook.dir/build.make CMakeFiles/test_hook.dir/tests/test_hook.cc.o
.PHONY : tests/test_hook.cc.o

tests/test_hook.i: tests/test_hook.cc.i
.PHONY : tests/test_hook.i

# target to preprocess a source file
tests/test_hook.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_hook.dir/build.make CMakeFiles/test_hook.dir/tests/test_hook.cc.i
.PHONY : tests/test_hook.cc.i

tests/test_hook.s: tests/test_hook.cc.s
.PHONY : tests/test_hook.s

# target to generate assembly for a file
tests/test_hook.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_hook.dir/build.make CMakeFiles/test_hook.dir/tests/test_hook.cc.s
.PHONY : tests/test_hook.cc.s

tests/test_iomanager.o: tests/test_iomanager.cc.o
.PHONY : tests/test_iomanager.o

# target to build an object file
tests/test_iomanager.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_iomanager.dir/build.make CMakeFiles/test_iomanager.dir/tests/test_iomanager.cc.o
.PHONY : tests/test_iomanager.cc.o

tests/test_iomanager.i: tests/test_iomanager.cc.i
.PHONY : tests/test_iomanager.i

# target to preprocess a source file
tests/test_iomanager.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_iomanager.dir/build.make CMakeFiles/test_iomanager.dir/tests/test_iomanager.cc.i
.PHONY : tests/test_iomanager.cc.i

tests/test_iomanager.s: tests/test_iomanager.cc.s
.PHONY : tests/test_iomanager.s

# target to generate assembly for a file
tests/test_iomanager.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_iomanager.dir/build.make CMakeFiles/test_iomanager.dir/tests/test_iomanager.cc.s
.PHONY : tests/test_iomanager.cc.s

tests/test_scheduler.o: tests/test_scheduler.cc.o
.PHONY : tests/test_scheduler.o

# target to build an object file
tests/test_scheduler.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_scheduler.dir/build.make CMakeFiles/test_scheduler.dir/tests/test_scheduler.cc.o
.PHONY : tests/test_scheduler.cc.o

tests/test_scheduler.i: tests/test_scheduler.cc.i
.PHONY : tests/test_scheduler.i

# target to preprocess a source file
tests/test_scheduler.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_scheduler.dir/build.make CMakeFiles/test_scheduler.dir/tests/test_scheduler.cc.i
.PHONY : tests/test_scheduler.cc.i

tests/test_scheduler.s: tests/test_scheduler.cc.s
.PHONY : tests/test_scheduler.s

# target to generate assembly for a file
tests/test_scheduler.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_scheduler.dir/build.make CMakeFiles/test_scheduler.dir/tests/test_scheduler.cc.s
.PHONY : tests/test_scheduler.cc.s

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

tests/test_util.o: tests/test_util.cc.o
.PHONY : tests/test_util.o

# target to build an object file
tests/test_util.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/tests/test_util.cc.o
.PHONY : tests/test_util.cc.o

tests/test_util.i: tests/test_util.cc.i
.PHONY : tests/test_util.i

# target to preprocess a source file
tests/test_util.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/tests/test_util.cc.i
.PHONY : tests/test_util.cc.i

tests/test_util.s: tests/test_util.cc.s
.PHONY : tests/test_util.s

# target to generate assembly for a file
tests/test_util.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/tests/test_util.cc.s
.PHONY : tests/test_util.cc.s

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
	@echo "... test_fiber"
	@echo "... test_hook"
	@echo "... test_iomanager"
	@echo "... test_scheduler"
	@echo "... test_thread"
	@echo "... test_util"
	@echo "... testlog"
	@echo "... DW/config.o"
	@echo "... DW/config.i"
	@echo "... DW/config.s"
	@echo "... DW/fd_manager.o"
	@echo "... DW/fd_manager.i"
	@echo "... DW/fd_manager.s"
	@echo "... DW/fiber.o"
	@echo "... DW/fiber.i"
	@echo "... DW/fiber.s"
	@echo "... DW/hook.o"
	@echo "... DW/hook.i"
	@echo "... DW/hook.s"
	@echo "... DW/iomanager.o"
	@echo "... DW/iomanager.i"
	@echo "... DW/iomanager.s"
	@echo "... DW/log.o"
	@echo "... DW/log.i"
	@echo "... DW/log.s"
	@echo "... DW/mutex.o"
	@echo "... DW/mutex.i"
	@echo "... DW/mutex.s"
	@echo "... DW/scheduler.o"
	@echo "... DW/scheduler.i"
	@echo "... DW/scheduler.s"
	@echo "... DW/thread.o"
	@echo "... DW/thread.i"
	@echo "... DW/thread.s"
	@echo "... DW/timer.o"
	@echo "... DW/timer.i"
	@echo "... DW/timer.s"
	@echo "... DW/util.o"
	@echo "... DW/util.i"
	@echo "... DW/util.s"
	@echo "... tests/test_config.o"
	@echo "... tests/test_config.i"
	@echo "... tests/test_config.s"
	@echo "... tests/test_fiber.o"
	@echo "... tests/test_fiber.i"
	@echo "... tests/test_fiber.s"
	@echo "... tests/test_hook.o"
	@echo "... tests/test_hook.i"
	@echo "... tests/test_hook.s"
	@echo "... tests/test_iomanager.o"
	@echo "... tests/test_iomanager.i"
	@echo "... tests/test_iomanager.s"
	@echo "... tests/test_scheduler.o"
	@echo "... tests/test_scheduler.i"
	@echo "... tests/test_scheduler.s"
	@echo "... tests/test_thread.o"
	@echo "... tests/test_thread.i"
	@echo "... tests/test_thread.s"
	@echo "... tests/test_util.o"
	@echo "... tests/test_util.i"
	@echo "... tests/test_util.s"
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

