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
CMAKE_COMMAND = "C:\Program Files (x86)\cmake-3.17.0-win64-x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\cmake-3.17.0-win64-x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\shell\Technion\MTM\ex1\build\mtm-1\mtm\ex1\wet_exercise

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\shell\Technion\MTM\ex1\build\mtm-1\mtm\ex1\wet_exercise\build

# Include any dependencies generated for this target.
include CMakeFiles/mtm_ex1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mtm_ex1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mtm_ex1.dir/flags.make

CMakeFiles/mtm_ex1.dir/map.c.obj: CMakeFiles/mtm_ex1.dir/flags.make
CMakeFiles/mtm_ex1.dir/map.c.obj: ../map.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\shell\Technion\MTM\ex1\build\mtm-1\mtm\ex1\wet_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mtm_ex1.dir/map.c.obj"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\mtm_ex1.dir\map.c.obj   -c C:\Users\shell\Technion\MTM\ex1\build\mtm-1\mtm\ex1\wet_exercise\map.c

CMakeFiles/mtm_ex1.dir/map.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mtm_ex1.dir/map.c.i"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\shell\Technion\MTM\ex1\build\mtm-1\mtm\ex1\wet_exercise\map.c > CMakeFiles\mtm_ex1.dir\map.c.i

CMakeFiles/mtm_ex1.dir/map.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mtm_ex1.dir/map.c.s"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\shell\Technion\MTM\ex1\build\mtm-1\mtm\ex1\wet_exercise\map.c -o CMakeFiles\mtm_ex1.dir\map.c.s

# Object files for target mtm_ex1
mtm_ex1_OBJECTS = \
"CMakeFiles/mtm_ex1.dir/map.c.obj"

# External object files for target mtm_ex1
mtm_ex1_EXTERNAL_OBJECTS =

mtm_ex1.exe: CMakeFiles/mtm_ex1.dir/map.c.obj
mtm_ex1.exe: CMakeFiles/mtm_ex1.dir/build.make
mtm_ex1.exe: CMakeFiles/mtm_ex1.dir/linklibs.rsp
mtm_ex1.exe: CMakeFiles/mtm_ex1.dir/objects1.rsp
mtm_ex1.exe: CMakeFiles/mtm_ex1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\shell\Technion\MTM\ex1\build\mtm-1\mtm\ex1\wet_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable mtm_ex1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\mtm_ex1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mtm_ex1.dir/build: mtm_ex1.exe

.PHONY : CMakeFiles/mtm_ex1.dir/build

CMakeFiles/mtm_ex1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\mtm_ex1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/mtm_ex1.dir/clean

CMakeFiles/mtm_ex1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\shell\Technion\MTM\ex1\build\mtm-1\mtm\ex1\wet_exercise C:\Users\shell\Technion\MTM\ex1\build\mtm-1\mtm\ex1\wet_exercise C:\Users\shell\Technion\MTM\ex1\build\mtm-1\mtm\ex1\wet_exercise\build C:\Users\shell\Technion\MTM\ex1\build\mtm-1\mtm\ex1\wet_exercise\build C:\Users\shell\Technion\MTM\ex1\build\mtm-1\mtm\ex1\wet_exercise\build\CMakeFiles\mtm_ex1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mtm_ex1.dir/depend

