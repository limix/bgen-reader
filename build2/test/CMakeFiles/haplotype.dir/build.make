# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /bgen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /bgen/build2

# Include any dependencies generated for this target.
include test/CMakeFiles/haplotype.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/haplotype.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/haplotype.dir/flags.make

test/CMakeFiles/haplotype.dir/haplotype.c.o: test/CMakeFiles/haplotype.dir/flags.make
test/CMakeFiles/haplotype.dir/haplotype.c.o: ../test/haplotype.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/bgen/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object test/CMakeFiles/haplotype.dir/haplotype.c.o"
	cd /bgen/build2/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/haplotype.dir/haplotype.c.o   -c /bgen/test/haplotype.c

test/CMakeFiles/haplotype.dir/haplotype.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/haplotype.dir/haplotype.c.i"
	cd /bgen/build2/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /bgen/test/haplotype.c > CMakeFiles/haplotype.dir/haplotype.c.i

test/CMakeFiles/haplotype.dir/haplotype.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/haplotype.dir/haplotype.c.s"
	cd /bgen/build2/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /bgen/test/haplotype.c -o CMakeFiles/haplotype.dir/haplotype.c.s

test/CMakeFiles/haplotype.dir/haplotype.c.o.requires:

.PHONY : test/CMakeFiles/haplotype.dir/haplotype.c.o.requires

test/CMakeFiles/haplotype.dir/haplotype.c.o.provides: test/CMakeFiles/haplotype.dir/haplotype.c.o.requires
	$(MAKE) -f test/CMakeFiles/haplotype.dir/build.make test/CMakeFiles/haplotype.dir/haplotype.c.o.provides.build
.PHONY : test/CMakeFiles/haplotype.dir/haplotype.c.o.provides

test/CMakeFiles/haplotype.dir/haplotype.c.o.provides.build: test/CMakeFiles/haplotype.dir/haplotype.c.o


# Object files for target haplotype
haplotype_OBJECTS = \
"CMakeFiles/haplotype.dir/haplotype.c.o"

# External object files for target haplotype
haplotype_EXTERNAL_OBJECTS =

test/haplotype: test/CMakeFiles/haplotype.dir/haplotype.c.o
test/haplotype: test/CMakeFiles/haplotype.dir/build.make
test/haplotype: libbgen.so.3.0.0
test/haplotype: /usr/lib/x86_64-linux-gnu/libz.so
test/haplotype: /usr/local/lib/libzstd.so
test/haplotype: /usr/local/lib/libathr.so
test/haplotype: test/CMakeFiles/haplotype.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/bgen/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable haplotype"
	cd /bgen/build2/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/haplotype.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/haplotype.dir/build: test/haplotype

.PHONY : test/CMakeFiles/haplotype.dir/build

test/CMakeFiles/haplotype.dir/requires: test/CMakeFiles/haplotype.dir/haplotype.c.o.requires

.PHONY : test/CMakeFiles/haplotype.dir/requires

test/CMakeFiles/haplotype.dir/clean:
	cd /bgen/build2/test && $(CMAKE_COMMAND) -P CMakeFiles/haplotype.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/haplotype.dir/clean

test/CMakeFiles/haplotype.dir/depend:
	cd /bgen/build2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /bgen /bgen/test /bgen/build2 /bgen/build2/test /bgen/build2/test/CMakeFiles/haplotype.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/haplotype.dir/depend

