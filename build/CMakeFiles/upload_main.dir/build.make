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
CMAKE_COMMAND = /home/mostafa/.local/lib/python3.8/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/mostafa/.local/lib/python3.8/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mostafa/msp430_dev

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mostafa/msp430_dev/build

# Utility rule file for upload_main.

# Include any custom commands dependencies for this target.
include CMakeFiles/upload_main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/upload_main.dir/progress.make

CMakeFiles/upload_main:
	/usr/bin/mspdebug -q olimex-iso-mk2 prog\ main.elf

upload_main: CMakeFiles/upload_main
upload_main: CMakeFiles/upload_main.dir/build.make
.PHONY : upload_main

# Rule to build all files generated by this target.
CMakeFiles/upload_main.dir/build: upload_main
.PHONY : CMakeFiles/upload_main.dir/build

CMakeFiles/upload_main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/upload_main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/upload_main.dir/clean

CMakeFiles/upload_main.dir/depend:
	cd /home/mostafa/msp430_dev/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mostafa/msp430_dev /home/mostafa/msp430_dev /home/mostafa/msp430_dev/build /home/mostafa/msp430_dev/build /home/mostafa/msp430_dev/build/CMakeFiles/upload_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/upload_main.dir/depend
