# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ian/Documents/Projects/DMC/simulationCode/DMCcpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ian/Documents/Projects/DMC/simulationCode/DMCcpp

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/ian/Documents/Projects/DMC/simulationCode/DMCcpp/CMakeFiles /home/ian/Documents/Projects/DMC/simulationCode/DMCcpp/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/ian/Documents/Projects/DMC/simulationCode/DMCcpp/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named dmcSim

# Build rule for target.
dmcSim: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 dmcSim
.PHONY : dmcSim

# fast build rule for target.
dmcSim/fast:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/build
.PHONY : dmcSim/fast

src/dmcSim.o: src/dmcSim.cpp.o

.PHONY : src/dmcSim.o

# target to build an object file
src/dmcSim.cpp.o:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/src/dmcSim.cpp.o
.PHONY : src/dmcSim.cpp.o

src/dmcSim.i: src/dmcSim.cpp.i

.PHONY : src/dmcSim.i

# target to preprocess a source file
src/dmcSim.cpp.i:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/src/dmcSim.cpp.i
.PHONY : src/dmcSim.cpp.i

src/dmcSim.s: src/dmcSim.cpp.s

.PHONY : src/dmcSim.s

# target to generate assembly for a file
src/dmcSim.cpp.s:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/src/dmcSim.cpp.s
.PHONY : src/dmcSim.cpp.s

src/inDMC.o: src/inDMC.cpp.o

.PHONY : src/inDMC.o

# target to build an object file
src/inDMC.cpp.o:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/src/inDMC.cpp.o
.PHONY : src/inDMC.cpp.o

src/inDMC.i: src/inDMC.cpp.i

.PHONY : src/inDMC.i

# target to preprocess a source file
src/inDMC.cpp.i:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/src/inDMC.cpp.i
.PHONY : src/inDMC.cpp.i

src/inDMC.s: src/inDMC.cpp.s

.PHONY : src/inDMC.s

# target to generate assembly for a file
src/inDMC.cpp.s:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/src/inDMC.cpp.s
.PHONY : src/inDMC.cpp.s

src/outDMC.o: src/outDMC.cpp.o

.PHONY : src/outDMC.o

# target to build an object file
src/outDMC.cpp.o:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/src/outDMC.cpp.o
.PHONY : src/outDMC.cpp.o

src/outDMC.i: src/outDMC.cpp.i

.PHONY : src/outDMC.i

# target to preprocess a source file
src/outDMC.cpp.i:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/src/outDMC.cpp.i
.PHONY : src/outDMC.cpp.i

src/outDMC.s: src/outDMC.cpp.s

.PHONY : src/outDMC.s

# target to generate assembly for a file
src/outDMC.cpp.s:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/src/outDMC.cpp.s
.PHONY : src/outDMC.cpp.s

src/runDMC.o: src/runDMC.cpp.o

.PHONY : src/runDMC.o

# target to build an object file
src/runDMC.cpp.o:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/src/runDMC.cpp.o
.PHONY : src/runDMC.cpp.o

src/runDMC.i: src/runDMC.cpp.i

.PHONY : src/runDMC.i

# target to preprocess a source file
src/runDMC.cpp.i:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/src/runDMC.cpp.i
.PHONY : src/runDMC.cpp.i

src/runDMC.s: src/runDMC.cpp.s

.PHONY : src/runDMC.s

# target to generate assembly for a file
src/runDMC.cpp.s:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/src/runDMC.cpp.s
.PHONY : src/runDMC.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... dmcSim"
	@echo "... src/dmcSim.o"
	@echo "... src/dmcSim.i"
	@echo "... src/dmcSim.s"
	@echo "... src/inDMC.o"
	@echo "... src/inDMC.i"
	@echo "... src/inDMC.s"
	@echo "... src/outDMC.o"
	@echo "... src/outDMC.i"
	@echo "... src/outDMC.s"
	@echo "... src/runDMC.o"
	@echo "... src/runDMC.i"
	@echo "... src/runDMC.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

