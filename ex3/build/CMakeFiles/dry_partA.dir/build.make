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
CMAKE_SOURCE_DIR = C:\VScode\ex3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\VScode\ex3\build

# Include any dependencies generated for this target.
include CMakeFiles/dry_partA.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dry_partA.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dry_partA.dir/flags.make

CMakeFiles/dry_partA.dir/temp.cpp.obj: CMakeFiles/dry_partA.dir/flags.make
CMakeFiles/dry_partA.dir/temp.cpp.obj: ../temp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\VScode\ex3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/dry_partA.dir/temp.cpp.obj"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\dry_partA.dir\temp.cpp.obj -c C:\VScode\ex3\temp.cpp

CMakeFiles/dry_partA.dir/temp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dry_partA.dir/temp.cpp.i"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\VScode\ex3\temp.cpp > CMakeFiles\dry_partA.dir\temp.cpp.i

CMakeFiles/dry_partA.dir/temp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dry_partA.dir/temp.cpp.s"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\VScode\ex3\temp.cpp -o CMakeFiles\dry_partA.dir\temp.cpp.s

# Object files for target dry_partA
dry_partA_OBJECTS = \
"CMakeFiles/dry_partA.dir/temp.cpp.obj"

# External object files for target dry_partA
dry_partA_EXTERNAL_OBJECTS =

dry_partA.exe: CMakeFiles/dry_partA.dir/temp.cpp.obj
dry_partA.exe: CMakeFiles/dry_partA.dir/build.make
dry_partA.exe: CMakeFiles/dry_partA.dir/linklibs.rsp
dry_partA.exe: CMakeFiles/dry_partA.dir/objects1.rsp
dry_partA.exe: CMakeFiles/dry_partA.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\VScode\ex3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable dry_partA.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\dry_partA.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dry_partA.dir/build: dry_partA.exe

.PHONY : CMakeFiles/dry_partA.dir/build

CMakeFiles/dry_partA.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\dry_partA.dir\cmake_clean.cmake
.PHONY : CMakeFiles/dry_partA.dir/clean

CMakeFiles/dry_partA.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\VScode\ex3 C:\VScode\ex3 C:\VScode\ex3\build C:\VScode\ex3\build C:\VScode\ex3\build\CMakeFiles\dry_partA.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dry_partA.dir/depend

