# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jjjjjjjiyun/CLionProjects/WordAnalyze

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jjjjjjjiyun/CLionProjects/WordAnalyze/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/WordAnalyze.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/WordAnalyze.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/WordAnalyze.dir/flags.make

CMakeFiles/WordAnalyze.dir/lexer.cpp.o: CMakeFiles/WordAnalyze.dir/flags.make
CMakeFiles/WordAnalyze.dir/lexer.cpp.o: ../lexer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jjjjjjjiyun/CLionProjects/WordAnalyze/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/WordAnalyze.dir/lexer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WordAnalyze.dir/lexer.cpp.o -c /Users/jjjjjjjiyun/CLionProjects/WordAnalyze/lexer.cpp

CMakeFiles/WordAnalyze.dir/lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WordAnalyze.dir/lexer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jjjjjjjiyun/CLionProjects/WordAnalyze/lexer.cpp > CMakeFiles/WordAnalyze.dir/lexer.cpp.i

CMakeFiles/WordAnalyze.dir/lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WordAnalyze.dir/lexer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jjjjjjjiyun/CLionProjects/WordAnalyze/lexer.cpp -o CMakeFiles/WordAnalyze.dir/lexer.cpp.s

# Object files for target WordAnalyze
WordAnalyze_OBJECTS = \
"CMakeFiles/WordAnalyze.dir/lexer.cpp.o"

# External object files for target WordAnalyze
WordAnalyze_EXTERNAL_OBJECTS =

WordAnalyze: CMakeFiles/WordAnalyze.dir/lexer.cpp.o
WordAnalyze: CMakeFiles/WordAnalyze.dir/build.make
WordAnalyze: CMakeFiles/WordAnalyze.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jjjjjjjiyun/CLionProjects/WordAnalyze/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable WordAnalyze"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WordAnalyze.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/WordAnalyze.dir/build: WordAnalyze

.PHONY : CMakeFiles/WordAnalyze.dir/build

CMakeFiles/WordAnalyze.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/WordAnalyze.dir/cmake_clean.cmake
.PHONY : CMakeFiles/WordAnalyze.dir/clean

CMakeFiles/WordAnalyze.dir/depend:
	cd /Users/jjjjjjjiyun/CLionProjects/WordAnalyze/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jjjjjjjiyun/CLionProjects/WordAnalyze /Users/jjjjjjjiyun/CLionProjects/WordAnalyze /Users/jjjjjjjiyun/CLionProjects/WordAnalyze/cmake-build-debug /Users/jjjjjjjiyun/CLionProjects/WordAnalyze/cmake-build-debug /Users/jjjjjjjiyun/CLionProjects/WordAnalyze/cmake-build-debug/CMakeFiles/WordAnalyze.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/WordAnalyze.dir/depend

