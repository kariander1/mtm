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
include CMakeFiles/election_tester_libmap.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/election_tester_libmap.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/election_tester_libmap.dir/flags.make

CMakeFiles/election_tester_libmap.dir/election.c.obj: CMakeFiles/election_tester_libmap.dir/flags.make
CMakeFiles/election_tester_libmap.dir/election.c.obj: ../election.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\VScode\ex1\wet_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/election_tester_libmap.dir/election.c.obj"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\election_tester_libmap.dir\election.c.obj   -c C:\VScode\ex1\wet_exercise\election.c

CMakeFiles/election_tester_libmap.dir/election.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/election_tester_libmap.dir/election.c.i"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\VScode\ex1\wet_exercise\election.c > CMakeFiles\election_tester_libmap.dir\election.c.i

CMakeFiles/election_tester_libmap.dir/election.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/election_tester_libmap.dir/election.c.s"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\VScode\ex1\wet_exercise\election.c -o CMakeFiles\election_tester_libmap.dir\election.c.s

CMakeFiles/election_tester_libmap.dir/area.c.obj: CMakeFiles/election_tester_libmap.dir/flags.make
CMakeFiles/election_tester_libmap.dir/area.c.obj: ../area.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\VScode\ex1\wet_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/election_tester_libmap.dir/area.c.obj"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\election_tester_libmap.dir\area.c.obj   -c C:\VScode\ex1\wet_exercise\area.c

CMakeFiles/election_tester_libmap.dir/area.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/election_tester_libmap.dir/area.c.i"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\VScode\ex1\wet_exercise\area.c > CMakeFiles\election_tester_libmap.dir\area.c.i

CMakeFiles/election_tester_libmap.dir/area.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/election_tester_libmap.dir/area.c.s"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\VScode\ex1\wet_exercise\area.c -o CMakeFiles\election_tester_libmap.dir\area.c.s

CMakeFiles/election_tester_libmap.dir/node_key_value.c.obj: CMakeFiles/election_tester_libmap.dir/flags.make
CMakeFiles/election_tester_libmap.dir/node_key_value.c.obj: ../node_key_value.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\VScode\ex1\wet_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/election_tester_libmap.dir/node_key_value.c.obj"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\election_tester_libmap.dir\node_key_value.c.obj   -c C:\VScode\ex1\wet_exercise\node_key_value.c

CMakeFiles/election_tester_libmap.dir/node_key_value.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/election_tester_libmap.dir/node_key_value.c.i"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\VScode\ex1\wet_exercise\node_key_value.c > CMakeFiles\election_tester_libmap.dir\node_key_value.c.i

CMakeFiles/election_tester_libmap.dir/node_key_value.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/election_tester_libmap.dir/node_key_value.c.s"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\VScode\ex1\wet_exercise\node_key_value.c -o CMakeFiles\election_tester_libmap.dir\node_key_value.c.s

CMakeFiles/election_tester_libmap.dir/utilities.c.obj: CMakeFiles/election_tester_libmap.dir/flags.make
CMakeFiles/election_tester_libmap.dir/utilities.c.obj: ../utilities.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\VScode\ex1\wet_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/election_tester_libmap.dir/utilities.c.obj"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\election_tester_libmap.dir\utilities.c.obj   -c C:\VScode\ex1\wet_exercise\utilities.c

CMakeFiles/election_tester_libmap.dir/utilities.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/election_tester_libmap.dir/utilities.c.i"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\VScode\ex1\wet_exercise\utilities.c > CMakeFiles\election_tester_libmap.dir\utilities.c.i

CMakeFiles/election_tester_libmap.dir/utilities.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/election_tester_libmap.dir/utilities.c.s"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\VScode\ex1\wet_exercise\utilities.c -o CMakeFiles\election_tester_libmap.dir\utilities.c.s

CMakeFiles/election_tester_libmap.dir/tests/shai_test_election.c.obj: CMakeFiles/election_tester_libmap.dir/flags.make
CMakeFiles/election_tester_libmap.dir/tests/shai_test_election.c.obj: ../tests/shai_test_election.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\VScode\ex1\wet_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/election_tester_libmap.dir/tests/shai_test_election.c.obj"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\election_tester_libmap.dir\tests\shai_test_election.c.obj   -c C:\VScode\ex1\wet_exercise\tests\shai_test_election.c

CMakeFiles/election_tester_libmap.dir/tests/shai_test_election.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/election_tester_libmap.dir/tests/shai_test_election.c.i"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\VScode\ex1\wet_exercise\tests\shai_test_election.c > CMakeFiles\election_tester_libmap.dir\tests\shai_test_election.c.i

CMakeFiles/election_tester_libmap.dir/tests/shai_test_election.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/election_tester_libmap.dir/tests/shai_test_election.c.s"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\VScode\ex1\wet_exercise\tests\shai_test_election.c -o CMakeFiles\election_tester_libmap.dir\tests\shai_test_election.c.s

# Object files for target election_tester_libmap
election_tester_libmap_OBJECTS = \
"CMakeFiles/election_tester_libmap.dir/election.c.obj" \
"CMakeFiles/election_tester_libmap.dir/area.c.obj" \
"CMakeFiles/election_tester_libmap.dir/node_key_value.c.obj" \
"CMakeFiles/election_tester_libmap.dir/utilities.c.obj" \
"CMakeFiles/election_tester_libmap.dir/tests/shai_test_election.c.obj"

# External object files for target election_tester_libmap
election_tester_libmap_EXTERNAL_OBJECTS =

election_tester_libmap.exe: CMakeFiles/election_tester_libmap.dir/election.c.obj
election_tester_libmap.exe: CMakeFiles/election_tester_libmap.dir/area.c.obj
election_tester_libmap.exe: CMakeFiles/election_tester_libmap.dir/node_key_value.c.obj
election_tester_libmap.exe: CMakeFiles/election_tester_libmap.dir/utilities.c.obj
election_tester_libmap.exe: CMakeFiles/election_tester_libmap.dir/tests/shai_test_election.c.obj
election_tester_libmap.exe: CMakeFiles/election_tester_libmap.dir/build.make
election_tester_libmap.exe: CMakeFiles/election_tester_libmap.dir/linklibs.rsp
election_tester_libmap.exe: CMakeFiles/election_tester_libmap.dir/objects1.rsp
election_tester_libmap.exe: CMakeFiles/election_tester_libmap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\VScode\ex1\wet_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable election_tester_libmap.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\election_tester_libmap.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/election_tester_libmap.dir/build: election_tester_libmap.exe

.PHONY : CMakeFiles/election_tester_libmap.dir/build

CMakeFiles/election_tester_libmap.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\election_tester_libmap.dir\cmake_clean.cmake
.PHONY : CMakeFiles/election_tester_libmap.dir/clean

CMakeFiles/election_tester_libmap.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\VScode\ex1\wet_exercise C:\VScode\ex1\wet_exercise C:\VScode\ex1\wet_exercise\build C:\VScode\ex1\wet_exercise\build C:\VScode\ex1\wet_exercise\build\CMakeFiles\election_tester_libmap.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/election_tester_libmap.dir/depend

