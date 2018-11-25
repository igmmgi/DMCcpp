# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_SOURCE_DIR = /home/ian/Desktop/DMCcpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ian/Desktop/DMCcpp

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
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
	$(CMAKE_COMMAND) -E cmake_progress_start /home/ian/Desktop/DMCcpp/CMakeFiles /home/ian/Desktop/DMCcpp/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/ian/Desktop/DMCcpp/CMakeFiles 0
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
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
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

inDMC.o: inDMC.cpp.o

.PHONY : inDMC.o

# target to build an object file
inDMC.cpp.o:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/inDMC.cpp.o
.PHONY : inDMC.cpp.o

inDMC.i: inDMC.cpp.i

.PHONY : inDMC.i

# target to preprocess a source file
inDMC.cpp.i:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/inDMC.cpp.i
.PHONY : inDMC.cpp.i

inDMC.s: inDMC.cpp.s

.PHONY : inDMC.s

# target to generate assembly for a file
inDMC.cpp.s:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/inDMC.cpp.s
.PHONY : inDMC.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/main.cpp.s
.PHONY : main.cpp.s

outDMC.o: outDMC.cpp.o

.PHONY : outDMC.o

# target to build an object file
outDMC.cpp.o:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/outDMC.cpp.o
.PHONY : outDMC.cpp.o

outDMC.i: outDMC.cpp.i

.PHONY : outDMC.i

# target to preprocess a source file
outDMC.cpp.i:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/outDMC.cpp.i
.PHONY : outDMC.cpp.i

outDMC.s: outDMC.cpp.s

.PHONY : outDMC.s

# target to generate assembly for a file
outDMC.cpp.s:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/outDMC.cpp.s
.PHONY : outDMC.cpp.s

runDMC.o: runDMC.cpp.o

.PHONY : runDMC.o

# target to build an object file
runDMC.cpp.o:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/runDMC.cpp.o
.PHONY : runDMC.cpp.o

runDMC.i: runDMC.cpp.i

.PHONY : runDMC.i

# target to preprocess a source file
runDMC.cpp.i:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/runDMC.cpp.i
.PHONY : runDMC.cpp.i

runDMC.s: runDMC.cpp.s

.PHONY : runDMC.s

# target to generate assembly for a file
runDMC.cpp.s:
	$(MAKE) -f CMakeFiles/dmcSim.dir/build.make CMakeFiles/dmcSim.dir/runDMC.cpp.s
.PHONY : runDMC.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... dmcSim"
	@echo "... edit_cache"
	@echo "... inDMC.o"
	@echo "... inDMC.i"
	@echo "... inDMC.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... outDMC.o"
	@echo "... outDMC.i"
	@echo "... outDMC.s"
	@echo "... runDMC.o"
	@echo "... runDMC.i"
	@echo "... runDMC.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

