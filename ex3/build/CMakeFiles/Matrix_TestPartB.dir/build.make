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
CMAKE_SOURCE_DIR = C:\VScode\mtm\ex3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\VScode\mtm\ex3\build

# Include any dependencies generated for this target.
include CMakeFiles/Matrix_TestPartB.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Matrix_TestPartB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Matrix_TestPartB.dir/flags.make

CMakeFiles/Matrix_TestPartB.dir/partB/test_partB.cpp.obj: CMakeFiles/Matrix_TestPartB.dir/flags.make
CMakeFiles/Matrix_TestPartB.dir/partB/test_partB.cpp.obj: ../partB/test_partB.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\VScode\mtm\ex3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Matrix_TestPartB.dir/partB/test_partB.cpp.obj"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Matrix_TestPartB.dir\partB\test_partB.cpp.obj -c C:\VScode\mtm\ex3\partB\test_partB.cpp

CMakeFiles/Matrix_TestPartB.dir/partB/test_partB.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Matrix_TestPartB.dir/partB/test_partB.cpp.i"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\VScode\mtm\ex3\partB\test_partB.cpp > CMakeFiles\Matrix_TestPartB.dir\partB\test_partB.cpp.i

CMakeFiles/Matrix_TestPartB.dir/partB/test_partB.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Matrix_TestPartB.dir/partB/test_partB.cpp.s"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\VScode\mtm\ex3\partB\test_partB.cpp -o CMakeFiles\Matrix_TestPartB.dir\partB\test_partB.cpp.s

CMakeFiles/Matrix_TestPartB.dir/partB/Auxiliaries.cpp.obj: CMakeFiles/Matrix_TestPartB.dir/flags.make
CMakeFiles/Matrix_TestPartB.dir/partB/Auxiliaries.cpp.obj: ../partB/Auxiliaries.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\VScode\mtm\ex3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Matrix_TestPartB.dir/partB/Auxiliaries.cpp.obj"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Matrix_TestPartB.dir\partB\Auxiliaries.cpp.obj -c C:\VScode\mtm\ex3\partB\Auxiliaries.cpp

CMakeFiles/Matrix_TestPartB.dir/partB/Auxiliaries.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Matrix_TestPartB.dir/partB/Auxiliaries.cpp.i"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\VScode\mtm\ex3\partB\Auxiliaries.cpp > CMakeFiles\Matrix_TestPartB.dir\partB\Auxiliaries.cpp.i

CMakeFiles/Matrix_TestPartB.dir/partB/Auxiliaries.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Matrix_TestPartB.dir/partB/Auxiliaries.cpp.s"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\VScode\mtm\ex3\partB\Auxiliaries.cpp -o CMakeFiles\Matrix_TestPartB.dir\partB\Auxiliaries.cpp.s

# Object files for target Matrix_TestPartB
Matrix_TestPartB_OBJECTS = \
"CMakeFiles/Matrix_TestPartB.dir/partB/test_partB.cpp.obj" \
"CMakeFiles/Matrix_TestPartB.dir/partB/Auxiliaries.cpp.obj"

# External object files for target Matrix_TestPartB
Matrix_TestPartB_EXTERNAL_OBJECTS =

Matrix_TestPartB.exe: CMakeFiles/Matrix_TestPartB.dir/partB/test_partB.cpp.obj
Matrix_TestPartB.exe: CMakeFiles/Matrix_TestPartB.dir/partB/Auxiliaries.cpp.obj
Matrix_TestPartB.exe: CMakeFiles/Matrix_TestPartB.dir/build.make
Matrix_TestPartB.exe: CMakeFiles/Matrix_TestPartB.dir/linklibs.rsp
Matrix_TestPartB.exe: CMakeFiles/Matrix_TestPartB.dir/objects1.rsp
Matrix_TestPartB.exe: CMakeFiles/Matrix_TestPartB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\VScode\mtm\ex3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Matrix_TestPartB.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Matrix_TestPartB.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Matrix_TestPartB.dir/build: Matrix_TestPartB.exe

.PHONY : CMakeFiles/Matrix_TestPartB.dir/build

CMakeFiles/Matrix_TestPartB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Matrix_TestPartB.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Matrix_TestPartB.dir/clean

CMakeFiles/Matrix_TestPartB.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\VScode\mtm\ex3 C:\VScode\mtm\ex3 C:\VScode\mtm\ex3\build C:\VScode\mtm\ex3\build C:\VScode\mtm\ex3\build\CMakeFiles\Matrix_TestPartB.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Matrix_TestPartB.dir/depend

