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
include CMakeFiles/map_group.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/map_group.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/map_group.dir/flags.make

CMakeFiles/map_group.dir/tests/test_map_from_group.c.obj: CMakeFiles/map_group.dir/flags.make
CMakeFiles/map_group.dir/tests/test_map_from_group.c.obj: ../tests/test_map_from_group.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\VScode\ex1\wet_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/map_group.dir/tests/test_map_from_group.c.obj"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\map_group.dir\tests\test_map_from_group.c.obj   -c C:\VScode\ex1\wet_exercise\tests\test_map_from_group.c

CMakeFiles/map_group.dir/tests/test_map_from_group.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/map_group.dir/tests/test_map_from_group.c.i"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\VScode\ex1\wet_exercise\tests\test_map_from_group.c > CMakeFiles\map_group.dir\tests\test_map_from_group.c.i

CMakeFiles/map_group.dir/tests/test_map_from_group.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/map_group.dir/tests/test_map_from_group.c.s"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\VScode\ex1\wet_exercise\tests\test_map_from_group.c -o CMakeFiles\map_group.dir\tests\test_map_from_group.c.s

CMakeFiles/map_group.dir/mtm_map/map.c.obj: CMakeFiles/map_group.dir/flags.make
CMakeFiles/map_group.dir/mtm_map/map.c.obj: ../mtm_map/map.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\VScode\ex1\wet_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/map_group.dir/mtm_map/map.c.obj"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\map_group.dir\mtm_map\map.c.obj   -c C:\VScode\ex1\wet_exercise\mtm_map\map.c

CMakeFiles/map_group.dir/mtm_map/map.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/map_group.dir/mtm_map/map.c.i"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\VScode\ex1\wet_exercise\mtm_map\map.c > CMakeFiles\map_group.dir\mtm_map\map.c.i

CMakeFiles/map_group.dir/mtm_map/map.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/map_group.dir/mtm_map/map.c.s"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\VScode\ex1\wet_exercise\mtm_map\map.c -o CMakeFiles\map_group.dir\mtm_map\map.c.s

CMakeFiles/map_group.dir/exutilities.c.obj: CMakeFiles/map_group.dir/flags.make
CMakeFiles/map_group.dir/exutilities.c.obj: ../exutilities.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\VScode\ex1\wet_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/map_group.dir/exutilities.c.obj"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\map_group.dir\exutilities.c.obj   -c C:\VScode\ex1\wet_exercise\exutilities.c

CMakeFiles/map_group.dir/exutilities.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/map_group.dir/exutilities.c.i"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\VScode\ex1\wet_exercise\exutilities.c > CMakeFiles\map_group.dir\exutilities.c.i

CMakeFiles/map_group.dir/exutilities.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/map_group.dir/exutilities.c.s"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\VScode\ex1\wet_exercise\exutilities.c -o CMakeFiles\map_group.dir\exutilities.c.s

CMakeFiles/map_group.dir/nodekeyvalue.c.obj: CMakeFiles/map_group.dir/flags.make
CMakeFiles/map_group.dir/nodekeyvalue.c.obj: ../nodekeyvalue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\VScode\ex1\wet_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/map_group.dir/nodekeyvalue.c.obj"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\map_group.dir\nodekeyvalue.c.obj   -c C:\VScode\ex1\wet_exercise\nodekeyvalue.c

CMakeFiles/map_group.dir/nodekeyvalue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/map_group.dir/nodekeyvalue.c.i"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\VScode\ex1\wet_exercise\nodekeyvalue.c > CMakeFiles\map_group.dir\nodekeyvalue.c.i

CMakeFiles/map_group.dir/nodekeyvalue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/map_group.dir/nodekeyvalue.c.s"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\VScode\ex1\wet_exercise\nodekeyvalue.c -o CMakeFiles\map_group.dir\nodekeyvalue.c.s

# Object files for target map_group
map_group_OBJECTS = \
"CMakeFiles/map_group.dir/tests/test_map_from_group.c.obj" \
"CMakeFiles/map_group.dir/mtm_map/map.c.obj" \
"CMakeFiles/map_group.dir/exutilities.c.obj" \
"CMakeFiles/map_group.dir/nodekeyvalue.c.obj"

# External object files for target map_group
map_group_EXTERNAL_OBJECTS =

map_group.exe: CMakeFiles/map_group.dir/tests/test_map_from_group.c.obj
map_group.exe: CMakeFiles/map_group.dir/mtm_map/map.c.obj
map_group.exe: CMakeFiles/map_group.dir/exutilities.c.obj
map_group.exe: CMakeFiles/map_group.dir/nodekeyvalue.c.obj
map_group.exe: CMakeFiles/map_group.dir/build.make
map_group.exe: CMakeFiles/map_group.dir/linklibs.rsp
map_group.exe: CMakeFiles/map_group.dir/objects1.rsp
map_group.exe: CMakeFiles/map_group.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\VScode\ex1\wet_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable map_group.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\map_group.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/map_group.dir/build: map_group.exe

.PHONY : CMakeFiles/map_group.dir/build

CMakeFiles/map_group.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\map_group.dir\cmake_clean.cmake
.PHONY : CMakeFiles/map_group.dir/clean

CMakeFiles/map_group.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\VScode\ex1\wet_exercise C:\VScode\ex1\wet_exercise C:\VScode\ex1\wet_exercise\build C:\VScode\ex1\wet_exercise\build C:\VScode\ex1\wet_exercise\build\CMakeFiles\map_group.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/map_group.dir/depend

