cmake_minimum_required(VERSION 3.18.4)
project(geostats_cvs_parser)
include(FetchContent)

set(CMAKE_CXX_STANDARD 14)
set(JSON_Install OFF CACHE INTERNAL "")

# It alleviates some issues on Windows systems about compile-option incompatibility.
# This forces a default behavior for the googletest to be compatible with the defaults on your own project.
set (gtest_force_shared_crt ON CACHE BOOL "MSVC defaults to shared CRT" FORCE)

# Fix for undefined reference to `pthread_create`
# https://stackoverflow.com/questions/53795731/undefined-reference-to-pthread-create-clion
set(CMAKE_CXX_FLAGS -pthread)
set(LIB_PATH lib)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e
)
FetchContent_Declare(
    sqlite3-cmake
    GIT_REPOSITORY https://github.com/alex85k/sqlite3-cmake.git
)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
)
FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
)
FetchContent_MakeAvailable(googletest sqlite3-cmake nlohmann_json httplib)

add_library(utils utils.cpp)

include_directories(${LIB_PATH}/cpp-httplib)

add_executable(geostats_cvs_parser main.cpp sql_statements.h)

target_compile_definitions(gtest
    PUBLIC
    GTEST_LANG_CXX20
    GTEST_HAS_TR1_TUPLE=0
)

# Executing this binary will run the test for us.
add_executable(tests)

target_sources(tests
    PRIVATE
    tests/SomeTests.cpp
)

# is only required to set some required properties for compatibility with googletest
set_target_properties(tests PROPERTIES COMPILE_FLAGS "${cxx_strict}")

# binary containing our tests should be linked against googletest as well as our own library
target_link_libraries(tests gtest gtest_main utils)

# Fix for "undefined reference to dlopen"
# ${CMAKE_DL_LIBS}
# https://gist.github.com/kwk/3595733
target_link_libraries(geostats_cvs_parser PRIVATE nlohmann_json::nlohmann_json sqlite3 httplib ${CMAKE_DL_LIBS} PUBLIC utils)