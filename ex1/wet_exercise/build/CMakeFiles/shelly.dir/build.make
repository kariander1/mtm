# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\VScode\ex1\wet_exercise

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\VScode\ex1\wet_exercise\build

# Include any dependencies generated for this target.
include CMakeFiles/shelly.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/shelly.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shelly.dir/flags.make

CMakeFiles/shelly.dir/mtm_map/node_key_value.c.obj: CMakeFiles/shelly.dir/flags.make
CMakeFiles/shelly.dir/mtm_map/node_key_value.c.obj: ../mtm_map/node_key_value.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\VScode\ex1\wet_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/shelly.dir/mtm_map/node_key_value.c.obj"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\shelly.dir\mtm_map\node_key_value.c.obj   -c C:\VScode\ex1\wet_exercise\mtm_map\node_key_value.c

CMakeFiles/shelly.dir/mtm_map/node_key_value.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shelly.dir/mtm_map/node_key_value.c.i"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\VScode\ex1\wet_exercise\mtm_map\node_key_value.c > CMakeFiles\shelly.dir\mtm_map\node_key_value.c.i

CMakeFiles/shelly.dir/mtm_map/node_key_value.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shelly.dir/mtm_map/node_key_value.c.s"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\VScode\ex1\wet_exercise\mtm_map\node_key_value.c -o CMakeFiles\shelly.dir\mtm_map\node_key_value.c.s

CMakeFiles/shelly.dir/election_utilities.c.obj: CMakeFiles/shelly.dir/flags.make
CMakeFiles/shelly.dir/election_utilities.c.obj: ../election_utilities.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\VScode\ex1\wet_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/shelly.dir/election_utilities.c.obj"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\shelly.dir\election_utilities.c.obj   -c C:\VScode\ex1\wet_exercise\election_utilities.c

CMakeFiles/shelly.dir/election_utilities.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shelly.dir/election_utilities.c.i"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\VScode\ex1\wet_exercise\election_utilities.c > CMakeFiles\shelly.dir\election_utilities.c.i

CMakeFiles/shelly.dir/election_utilities.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shelly.dir/election_utilities.c.s"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\VScode\ex1\wet_exercise\election_utilities.c -o CMakeFiles\shelly.dir\election_utilities.c.s

# Object files for target shelly
shelly_OBJECTS = \
"CMakeFiles/shelly.dir/mtm_map/node_key_value.c.obj" \
"CMakeFiles/shelly.dir/election_utilities.c.obj"

# External object files for target shelly
shelly_EXTERNAL_OBJECTS =

shelly.exe: CMakeFiles/shelly.dir/mtm_map/node_key_value.c.obj
shelly.exe: CMakeFiles/shelly.dir/election_utilities.c.obj
shelly.exe: CMakeFiles/shelly.dir/build.make
shelly.exe: CMakeFiles/shelly.dir/linklibs.rsp
shelly.exe: CMakeFiles/shelly.dir/objects1.rsp
shelly.exe: CMakeFiles/shelly.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\VScode\ex1\wet_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable shelly.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\shelly.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/shelly.dir/build: shelly.exe

.PHONY : CMakeFiles/shelly.dir/build

CMakeFiles/shelly.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\shelly.dir\cmake_clean.cmake
.PHONY : CMakeFiles/shelly.dir/clean

CMakeFiles/shelly.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\VScode\ex1\wet_exercise C:\VScode\ex1\wet_exercise C:\VScode\ex1\wet_exercise\build C:\VScode\ex1\wet_exercise\build C:\VScode\ex1\wet_exercise\build\CMakeFiles\shelly.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/shelly.dir/depend

