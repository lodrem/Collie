# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/gallon/workSpace/private/Collie

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gallon/workSpace/private/Collie/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/logger.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/logger.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/logger.dir/flags.make

examples/CMakeFiles/logger.dir/logger.cc.o: examples/CMakeFiles/logger.dir/flags.make
examples/CMakeFiles/logger.dir/logger.cc.o: ../examples/logger.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gallon/workSpace/private/Collie/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/logger.dir/logger.cc.o"
	cd /home/gallon/workSpace/private/Collie/build/examples && /usr/bin/clang++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/logger.dir/logger.cc.o -c /home/gallon/workSpace/private/Collie/examples/logger.cc

examples/CMakeFiles/logger.dir/logger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/logger.dir/logger.cc.i"
	cd /home/gallon/workSpace/private/Collie/build/examples && /usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gallon/workSpace/private/Collie/examples/logger.cc > CMakeFiles/logger.dir/logger.cc.i

examples/CMakeFiles/logger.dir/logger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/logger.dir/logger.cc.s"
	cd /home/gallon/workSpace/private/Collie/build/examples && /usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gallon/workSpace/private/Collie/examples/logger.cc -o CMakeFiles/logger.dir/logger.cc.s

examples/CMakeFiles/logger.dir/logger.cc.o.requires:

.PHONY : examples/CMakeFiles/logger.dir/logger.cc.o.requires

examples/CMakeFiles/logger.dir/logger.cc.o.provides: examples/CMakeFiles/logger.dir/logger.cc.o.requires
	$(MAKE) -f examples/CMakeFiles/logger.dir/build.make examples/CMakeFiles/logger.dir/logger.cc.o.provides.build
.PHONY : examples/CMakeFiles/logger.dir/logger.cc.o.provides

examples/CMakeFiles/logger.dir/logger.cc.o.provides.build: examples/CMakeFiles/logger.dir/logger.cc.o


# Object files for target logger
logger_OBJECTS = \
"CMakeFiles/logger.dir/logger.cc.o"

# External object files for target logger
logger_EXTERNAL_OBJECTS =

examples/logger: examples/CMakeFiles/logger.dir/logger.cc.o
examples/logger: examples/CMakeFiles/logger.dir/build.make
examples/logger: lib/libcollie.a
examples/logger: examples/CMakeFiles/logger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gallon/workSpace/private/Collie/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable logger"
	cd /home/gallon/workSpace/private/Collie/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/logger.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/logger.dir/build: examples/logger

.PHONY : examples/CMakeFiles/logger.dir/build

examples/CMakeFiles/logger.dir/requires: examples/CMakeFiles/logger.dir/logger.cc.o.requires

.PHONY : examples/CMakeFiles/logger.dir/requires

examples/CMakeFiles/logger.dir/clean:
	cd /home/gallon/workSpace/private/Collie/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/logger.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/logger.dir/clean

examples/CMakeFiles/logger.dir/depend:
	cd /home/gallon/workSpace/private/Collie/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gallon/workSpace/private/Collie /home/gallon/workSpace/private/Collie/examples /home/gallon/workSpace/private/Collie/build /home/gallon/workSpace/private/Collie/build/examples /home/gallon/workSpace/private/Collie/build/examples/CMakeFiles/logger.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/logger.dir/depend

