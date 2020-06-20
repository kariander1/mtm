# The following is required by CMake
#cmake_minimum_required(VERSION 3.0.0)
# Set hw0 as the project name, C as the target language
# A project can contain multiple build products
#project(hw3 VERSION 0.1.0 LANGUAGES C++)
# # (Optionally uncomment): see more output from cmake during build,
# # including specific gcc command(s).
# set(CMAKE_VERBOSE_MAKEFILE ON)
# Set variables holding flags for gcc
#set(MTM_FLAGS_DEBUG "-std=c++11 -std= -Wall -Werror -pedantic-errors")
#set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDBUG")
# Set the flags for gcc (can also be done using target_compile_options and a couple of other ways)
#set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})
# Tell CMake to build an executable named mtm_tot, specifying the comprising file(s)

cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(IntMatrix VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG)


# EXE for tester
add_executable(intMatrix_Tester ./partA/tester.cpp ./partA/intMatrix.cpp ./partA/Auxiliaries.cpp)

# EXE for test_partA.cpp
add_executable(intMatrix_TestPartA ./partA/test_partA.cpp ./partA/intMatrix.cpp ./partA/Auxiliaries.cpp)

# EXE for test_partB.cpp
add_executable(Matrix_TestPartB ./partB/test_partB.cpp ./partB/Matrix.cpp  ./partB/Auxiliaries.cpp)

# EXE for matrix tester
add_executable(MatrixTester ./partB/MatrixTester.cpp ./partB/Auxiliaries.cpp  ./partA/IntMatrix.cpp)


# EXE for partC
add_executable(test_part_C ./partC/GameTest.cpp ./partC/Auxiliaries.cpp ./partC/Game.cpp ./partC/Soldier.cpp ./partC/Medic.cpp ./partC/Sniper.cpp ./partC/Character.cpp)
