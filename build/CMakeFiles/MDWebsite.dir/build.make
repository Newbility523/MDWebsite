# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/carl/MDWebsite

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/carl/MDWebsite/build

# Include any dependencies generated for this target.
include CMakeFiles/MDWebsite.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MDWebsite.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MDWebsite.dir/flags.make

CMakeFiles/MDWebsite.dir/src/main.cpp.o: CMakeFiles/MDWebsite.dir/flags.make
CMakeFiles/MDWebsite.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/carl/MDWebsite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MDWebsite.dir/src/main.cpp.o"
	/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MDWebsite.dir/src/main.cpp.o -c /home/carl/MDWebsite/src/main.cpp

CMakeFiles/MDWebsite.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MDWebsite.dir/src/main.cpp.i"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/carl/MDWebsite/src/main.cpp > CMakeFiles/MDWebsite.dir/src/main.cpp.i

CMakeFiles/MDWebsite.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MDWebsite.dir/src/main.cpp.s"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/carl/MDWebsite/src/main.cpp -o CMakeFiles/MDWebsite.dir/src/main.cpp.s

# Object files for target MDWebsite
MDWebsite_OBJECTS = \
"CMakeFiles/MDWebsite.dir/src/main.cpp.o"

# External object files for target MDWebsite
MDWebsite_EXTERNAL_OBJECTS =

MDWebsite: CMakeFiles/MDWebsite.dir/src/main.cpp.o
MDWebsite: CMakeFiles/MDWebsite.dir/build.make
MDWebsite: CMakeFiles/MDWebsite.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/carl/MDWebsite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MDWebsite"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MDWebsite.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MDWebsite.dir/build: MDWebsite

.PHONY : CMakeFiles/MDWebsite.dir/build

CMakeFiles/MDWebsite.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MDWebsite.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MDWebsite.dir/clean

CMakeFiles/MDWebsite.dir/depend:
	cd /home/carl/MDWebsite/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/carl/MDWebsite /home/carl/MDWebsite /home/carl/MDWebsite/build /home/carl/MDWebsite/build /home/carl/MDWebsite/build/CMakeFiles/MDWebsite.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MDWebsite.dir/depend

