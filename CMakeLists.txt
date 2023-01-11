cmake_minimum_required(VERSION 3.16)
project(Project)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


###############################################################################
## file globbing ##############################################################
###############################################################################

# These instructions search the directory tree when cmake is
# invoked and put all files that match the pattern in the variables 
# `sources` and `data`.
file(GLOB_RECURSE sources src/*.cpp src/*.h)
file(GLOB_RECURSE sources_test test/*.cpp test/*.h)
#file(GLOB_RECURSE data resources/*)


###############################################################################
## target definitions #########################################################
###############################################################################

# The data is just added to the executable, because in some IDEs (QtCreator) 
# files are invisible when they are not explicitly part of the project.
add_executable(app ${sources})

# Just for example add some compiler flags.
#target_compile_options(app PUBLIC -std=c++1y -Wall -Wfloat-conversion)

# This allows to include files relative to the root of the src directory with a <> pair
target_include_directories(app PUBLIC src)

# This copies all resource files in the build directory.
# We need this, because we want to work with paths relative to the executable.
#file(COPY ${data} DESTINATION resources)


###############################################################################
## testing ####################################################################
###############################################################################
enable_testing()

include(FetchContent)
include(GoogleTest)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(unit_tests ${sources_test})

# This allows us to use the executable as a link library, and inherit all 
# linker options and library dependencies from it, by simply adding it as dependency.
set_target_properties(app PROPERTIES ENABLE_EXPORTS on)

target_link_libraries(unit_tests
    PRIVATE
    GTest::GTest
    app
)

gtest_discover_tests(unit_tests)

