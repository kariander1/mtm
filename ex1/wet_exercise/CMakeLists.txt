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
#add_executable(mtm_ex mtm_election/election.c mtm_election/area.c mtm_map/map.c mtm_election/electionUtils.c)
#add_executable(mtm_ex election.c area.c mtm_map/map.c election_utilities.c tests/shai_test_election.c)
add_executable(mtm_ex tests/shai_test.c mtm_map/map.c election_utilities.c mtm_map/node_key_value.c)
#add_executable(mtm_node mtm_map/node_key_value.c election_utilities.c)