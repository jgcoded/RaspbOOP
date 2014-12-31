# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.1

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jgcoded/projects/RaspbOOP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jgcoded/projects/RaspbOOP/build

# Include any dependencies generated for this target.
include test/CMakeFiles/sensors.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/sensors.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/sensors.dir/flags.make

test/CMakeFiles/sensors.dir/sensors.cpp.o: test/CMakeFiles/sensors.dir/flags.make
test/CMakeFiles/sensors.dir/sensors.cpp.o: ../test/sensors.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jgcoded/projects/RaspbOOP/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/sensors.dir/sensors.cpp.o"
	cd /home/jgcoded/projects/RaspbOOP/build/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sensors.dir/sensors.cpp.o -c /home/jgcoded/projects/RaspbOOP/test/sensors.cpp

test/CMakeFiles/sensors.dir/sensors.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sensors.dir/sensors.cpp.i"
	cd /home/jgcoded/projects/RaspbOOP/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jgcoded/projects/RaspbOOP/test/sensors.cpp > CMakeFiles/sensors.dir/sensors.cpp.i

test/CMakeFiles/sensors.dir/sensors.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sensors.dir/sensors.cpp.s"
	cd /home/jgcoded/projects/RaspbOOP/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jgcoded/projects/RaspbOOP/test/sensors.cpp -o CMakeFiles/sensors.dir/sensors.cpp.s

test/CMakeFiles/sensors.dir/sensors.cpp.o.requires:
.PHONY : test/CMakeFiles/sensors.dir/sensors.cpp.o.requires

test/CMakeFiles/sensors.dir/sensors.cpp.o.provides: test/CMakeFiles/sensors.dir/sensors.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/sensors.dir/build.make test/CMakeFiles/sensors.dir/sensors.cpp.o.provides.build
.PHONY : test/CMakeFiles/sensors.dir/sensors.cpp.o.provides

test/CMakeFiles/sensors.dir/sensors.cpp.o.provides.build: test/CMakeFiles/sensors.dir/sensors.cpp.o

# Object files for target sensors
sensors_OBJECTS = \
"CMakeFiles/sensors.dir/sensors.cpp.o"

# External object files for target sensors
sensors_EXTERNAL_OBJECTS =

../bin/sensors: test/CMakeFiles/sensors.dir/sensors.cpp.o
../bin/sensors: test/CMakeFiles/sensors.dir/build.make
../bin/sensors: ../bin/libraspboop.so
../bin/sensors: /usr/lib/x86_64-linux-gnu/libSM.so
../bin/sensors: /usr/lib/x86_64-linux-gnu/libICE.so
../bin/sensors: /usr/lib/x86_64-linux-gnu/libX11.so
../bin/sensors: /usr/lib/x86_64-linux-gnu/libXext.so
../bin/sensors: /usr/lib/libwiringPi.so
../bin/sensors: /usr/local/lib/libboost_system.so
../bin/sensors: /usr/local/lib/libboost_regex.so
../bin/sensors: test/CMakeFiles/sensors.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/sensors"
	cd /home/jgcoded/projects/RaspbOOP/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sensors.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/sensors.dir/build: ../bin/sensors
.PHONY : test/CMakeFiles/sensors.dir/build

test/CMakeFiles/sensors.dir/requires: test/CMakeFiles/sensors.dir/sensors.cpp.o.requires
.PHONY : test/CMakeFiles/sensors.dir/requires

test/CMakeFiles/sensors.dir/clean:
	cd /home/jgcoded/projects/RaspbOOP/build/test && $(CMAKE_COMMAND) -P CMakeFiles/sensors.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/sensors.dir/clean

test/CMakeFiles/sensors.dir/depend:
	cd /home/jgcoded/projects/RaspbOOP/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jgcoded/projects/RaspbOOP /home/jgcoded/projects/RaspbOOP/test /home/jgcoded/projects/RaspbOOP/build /home/jgcoded/projects/RaspbOOP/build/test /home/jgcoded/projects/RaspbOOP/build/test/CMakeFiles/sensors.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/sensors.dir/depend
