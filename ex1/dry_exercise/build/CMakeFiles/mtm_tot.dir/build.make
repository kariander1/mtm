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
CMAKE_SOURCE_DIR = C:\VScode\mtm\ex1\dry_exercise

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\VScode\mtm\ex1\dry_exercise\build

# Include any dependencies generated for this target.
include CMakeFiles/mtm_tot.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mtm_tot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mtm_tot.dir/flags.make

CMakeFiles/mtm_tot.dir/exercise1_2_1.c.obj: CMakeFiles/mtm_tot.dir/flags.make
CMakeFiles/mtm_tot.dir/exercise1_2_1.c.obj: ../exercise1_2_1.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\VScode\mtm\ex1\dry_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mtm_tot.dir/exercise1_2_1.c.obj"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\mtm_tot.dir\exercise1_2_1.c.obj   -c C:\VScode\mtm\ex1\dry_exercise\exercise1_2_1.c

CMakeFiles/mtm_tot.dir/exercise1_2_1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mtm_tot.dir/exercise1_2_1.c.i"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\VScode\mtm\ex1\dry_exercise\exercise1_2_1.c > CMakeFiles\mtm_tot.dir\exercise1_2_1.c.i

CMakeFiles/mtm_tot.dir/exercise1_2_1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mtm_tot.dir/exercise1_2_1.c.s"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\VScode\mtm\ex1\dry_exercise\exercise1_2_1.c -o CMakeFiles\mtm_tot.dir\exercise1_2_1.c.s

# Object files for target mtm_tot
mtm_tot_OBJECTS = \
"CMakeFiles/mtm_tot.dir/exercise1_2_1.c.obj"

# External object files for target mtm_tot
mtm_tot_EXTERNAL_OBJECTS =

mtm_tot.exe: CMakeFiles/mtm_tot.dir/exercise1_2_1.c.obj
mtm_tot.exe: CMakeFiles/mtm_tot.dir/build.make
mtm_tot.exe: CMakeFiles/mtm_tot.dir/linklibs.rsp
mtm_tot.exe: CMakeFiles/mtm_tot.dir/objects1.rsp
mtm_tot.exe: CMakeFiles/mtm_tot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\VScode\mtm\ex1\dry_exercise\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable mtm_tot.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\mtm_tot.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mtm_tot.dir/build: mtm_tot.exe

.PHONY : CMakeFiles/mtm_tot.dir/build

CMakeFiles/mtm_tot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\mtm_tot.dir\cmake_clean.cmake
.PHONY : CMakeFiles/mtm_tot.dir/clean

CMakeFiles/mtm_tot.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\VScode\mtm\ex1\dry_exercise C:\VScode\mtm\ex1\dry_exercise C:\VScode\mtm\ex1\dry_exercise\build C:\VScode\mtm\ex1\dry_exercise\build C:\VScode\mtm\ex1\dry_exercise\build\CMakeFiles\mtm_tot.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mtm_tot.dir/depend

