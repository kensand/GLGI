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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kenny/git/GLGI/windows/GLGI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kenny/git/GLGI/windows/GLGI/build

# Include any dependencies generated for this target.
include GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/depend.make

# Include the progress variables for this target.
include GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/progress.make

# Include the compile flags for this target's objects.
include GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/flags.make

GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/__/__/src/glew.c.o: GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/flags.make
GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/__/__/src/glew.c.o: ../GLGI_64/deps/glew/src/glew.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kenny/git/GLGI/windows/GLGI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/__/__/src/glew.c.o"
	cd /home/kenny/git/GLGI/windows/GLGI/build/GLGI_64/deps/glew/build/cmake && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glew.dir/__/__/src/glew.c.o   -c /home/kenny/git/GLGI/windows/GLGI/GLGI_64/deps/glew/src/glew.c

GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/__/__/src/glew.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glew.dir/__/__/src/glew.c.i"
	cd /home/kenny/git/GLGI/windows/GLGI/build/GLGI_64/deps/glew/build/cmake && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kenny/git/GLGI/windows/GLGI/GLGI_64/deps/glew/src/glew.c > CMakeFiles/glew.dir/__/__/src/glew.c.i

GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/__/__/src/glew.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glew.dir/__/__/src/glew.c.s"
	cd /home/kenny/git/GLGI/windows/GLGI/build/GLGI_64/deps/glew/build/cmake && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kenny/git/GLGI/windows/GLGI/GLGI_64/deps/glew/src/glew.c -o CMakeFiles/glew.dir/__/__/src/glew.c.s

# Object files for target glew
glew_OBJECTS = \
"CMakeFiles/glew.dir/__/__/src/glew.c.o"

# External object files for target glew
glew_EXTERNAL_OBJECTS =

lib/libGLEW.so.2.1.0: GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/__/__/src/glew.c.o
lib/libGLEW.so.2.1.0: GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/build.make
lib/libGLEW.so.2.1.0: /usr/lib/libGL.so
lib/libGLEW.so.2.1.0: /usr/lib/libGLU.so
lib/libGLEW.so.2.1.0: GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kenny/git/GLGI/windows/GLGI/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library ../../../../../lib/libGLEW.so"
	cd /home/kenny/git/GLGI/windows/GLGI/build/GLGI_64/deps/glew/build/cmake && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glew.dir/link.txt --verbose=$(VERBOSE)
	cd /home/kenny/git/GLGI/windows/GLGI/build/GLGI_64/deps/glew/build/cmake && $(CMAKE_COMMAND) -E cmake_symlink_library ../../../../../lib/libGLEW.so.2.1.0 ../../../../../lib/libGLEW.so.2.1 ../../../../../lib/libGLEW.so

lib/libGLEW.so.2.1: lib/libGLEW.so.2.1.0
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libGLEW.so.2.1

lib/libGLEW.so: lib/libGLEW.so.2.1.0
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libGLEW.so

# Rule to build all files generated by this target.
GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/build: lib/libGLEW.so

.PHONY : GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/build

GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/clean:
	cd /home/kenny/git/GLGI/windows/GLGI/build/GLGI_64/deps/glew/build/cmake && $(CMAKE_COMMAND) -P CMakeFiles/glew.dir/cmake_clean.cmake
.PHONY : GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/clean

GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/depend:
	cd /home/kenny/git/GLGI/windows/GLGI/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kenny/git/GLGI/windows/GLGI /home/kenny/git/GLGI/windows/GLGI/GLGI_64/deps/glew/build/cmake /home/kenny/git/GLGI/windows/GLGI/build /home/kenny/git/GLGI/windows/GLGI/build/GLGI_64/deps/glew/build/cmake /home/kenny/git/GLGI/windows/GLGI/build/GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : GLGI_64/deps/glew/build/cmake/CMakeFiles/glew.dir/depend

