# The following is required by CMake
cmake_minimum_required(VERSION 3.0.0)
# Set hw0 as the project name, C as the target language
# A project can contain multiple build products
project(hw1 VERSION 0.1.0 LANGUAGES C)
# # (Optionally uncomment): see more output from cmake during build,
# # including specific gcc command(s).
# set(CMAKE_VERBOSE_MAKEFILE ON)
# Set variables holding flags for gcc
set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror -DNDEBUG=1")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDBUG")
# Set the flags for gcc (can also be done using target_compile_options and a couple of other ways)
set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})
# Tell CMake to build an executable named mtm_tot, specifying the comprising file(s)



# EXE for map with given tests
add_executable(map tests/map_example_test.c mtm_map/map.c election_utilities.c mtm_map/node_key_value.c)

# EXE for map with given tests from group
add_executable(map_group tests/test_map_from_group.c mtm_map/map.c election_utilities.c mtm_map/node_key_value.c)

# EXE for election with given tests
add_executable(election election.c area.c mtm_map/map.c mtm_map/node_key_value.c election_utilities.c tests/electionTestsExample.c)

# EXE for map_tester with our tester
add_executable(map_tester tests/shai_test.c mtm_map/map.c election_utilities.c mtm_map/node_key_value.c)

# EXE for election_tester with our tester
add_executable(election_tester election.c area.c mtm_map/map.c mtm_map/node_key_value.c election_utilities.c tests/shai_test_election.c)

# EXE for election_tester with our tester linked with given map
link_directories(.)
add_executable(election_tester_libmap election.c area.c mtm_map/node_key_value.c election_utilities.c tests/shai_test_election.c)
target_link_libraries(election_tester_libmap libmap.a)



#add_executable(mtm_node mtm_map/node_key_value.c election_utilities.c)