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
CMAKE_SOURCE_DIR = /home/tom/Development/xTetris

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tom/Development/xTetris/cmake-build-wsl_debug

# Include any dependencies generated for this target.
include CMakeFiles/xTetris.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/xTetris.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/xTetris.dir/flags.make

CMakeFiles/xTetris.dir/src/game.c.o: CMakeFiles/xTetris.dir/flags.make
CMakeFiles/xTetris.dir/src/game.c.o: ../src/game.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom/Development/xTetris/cmake-build-wsl_debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/xTetris.dir/src/game.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/xTetris.dir/src/game.c.o   -c /home/tom/Development/xTetris/src/game.c

CMakeFiles/xTetris.dir/src/game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/xTetris.dir/src/game.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom/Development/xTetris/src/game.c > CMakeFiles/xTetris.dir/src/game.c.i

CMakeFiles/xTetris.dir/src/game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/xTetris.dir/src/game.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom/Development/xTetris/src/game.c -o CMakeFiles/xTetris.dir/src/game.c.s

CMakeFiles/xTetris.dir/src/cpu.c.o: CMakeFiles/xTetris.dir/flags.make
CMakeFiles/xTetris.dir/src/cpu.c.o: ../src/cpu.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom/Development/xTetris/cmake-build-wsl_debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/xTetris.dir/src/cpu.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/xTetris.dir/src/cpu.c.o   -c /home/tom/Development/xTetris/src/cpu.c

CMakeFiles/xTetris.dir/src/cpu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/xTetris.dir/src/cpu.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom/Development/xTetris/src/cpu.c > CMakeFiles/xTetris.dir/src/cpu.c.i

CMakeFiles/xTetris.dir/src/cpu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/xTetris.dir/src/cpu.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom/Development/xTetris/src/cpu.c -o CMakeFiles/xTetris.dir/src/cpu.c.s

CMakeFiles/xTetris.dir/src/pieces.c.o: CMakeFiles/xTetris.dir/flags.make
CMakeFiles/xTetris.dir/src/pieces.c.o: ../src/pieces.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom/Development/xTetris/cmake-build-wsl_debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/xTetris.dir/src/pieces.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/xTetris.dir/src/pieces.c.o   -c /home/tom/Development/xTetris/src/pieces.c

CMakeFiles/xTetris.dir/src/pieces.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/xTetris.dir/src/pieces.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom/Development/xTetris/src/pieces.c > CMakeFiles/xTetris.dir/src/pieces.c.i

CMakeFiles/xTetris.dir/src/pieces.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/xTetris.dir/src/pieces.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom/Development/xTetris/src/pieces.c -o CMakeFiles/xTetris.dir/src/pieces.c.s

CMakeFiles/xTetris.dir/src/players.c.o: CMakeFiles/xTetris.dir/flags.make
CMakeFiles/xTetris.dir/src/players.c.o: ../src/players.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tom/Development/xTetris/cmake-build-wsl_debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/xTetris.dir/src/players.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/xTetris.dir/src/players.c.o   -c /home/tom/Development/xTetris/src/players.c

CMakeFiles/xTetris.dir/src/players.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/xTetris.dir/src/players.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom/Development/xTetris/src/players.c > CMakeFiles/xTetris.dir/src/players.c.i

CMakeFiles/xTetris.dir/src/players.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/xTetris.dir/src/players.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom/Development/xTetris/src/players.c -o CMakeFiles/xTetris.dir/src/players.c.s

# Object files for target xTetris
xTetris_OBJECTS = \
"CMakeFiles/xTetris.dir/src/game.c.o" \
"CMakeFiles/xTetris.dir/src/cpu.c.o" \
"CMakeFiles/xTetris.dir/src/pieces.c.o" \
"CMakeFiles/xTetris.dir/src/players.c.o"

# External object files for target xTetris
xTetris_EXTERNAL_OBJECTS =

xTetris: CMakeFiles/xTetris.dir/src/game.c.o
xTetris: CMakeFiles/xTetris.dir/src/cpu.c.o
xTetris: CMakeFiles/xTetris.dir/src/pieces.c.o
xTetris: CMakeFiles/xTetris.dir/src/players.c.o
xTetris: CMakeFiles/xTetris.dir/build.make
xTetris: CMakeFiles/xTetris.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tom/Development/xTetris/cmake-build-wsl_debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable xTetris"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/xTetris.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/xTetris.dir/build: xTetris

.PHONY : CMakeFiles/xTetris.dir/build

CMakeFiles/xTetris.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/xTetris.dir/cmake_clean.cmake
.PHONY : CMakeFiles/xTetris.dir/clean

CMakeFiles/xTetris.dir/depend:
	cd /home/tom/Development/xTetris/cmake-build-wsl_debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tom/Development/xTetris /home/tom/Development/xTetris /home/tom/Development/xTetris/cmake-build-wsl_debug /home/tom/Development/xTetris/cmake-build-wsl_debug /home/tom/Development/xTetris/cmake-build-wsl_debug/CMakeFiles/xTetris.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/xTetris.dir/depend

