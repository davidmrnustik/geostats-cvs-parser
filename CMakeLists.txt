cmake_minimum_required(VERSION 3.18.4)
project(geostats_cvs_parser)

set(CMAKE_CXX_STANDARD 14)

set(JSON_Install OFF CACHE INTERNAL "")

# It alleviates some issues on Windows systems about compile-option incompatibility.
# This forces a default behavior for the googletest to be compatible with the defaults on your own project.
set (gtest_force_shared_crt ON CACHE BOOL "MSVC defaults to shared CRT" FORCE)

#find_package(json 3.2.0 REQUIRED)

# Fix for undefined reference to `pthread_create`
# https://stackoverflow.com/questions/53795731/undefined-reference-to-pthread-create-clion
set(CMAKE_CXX_FLAGS -pthread)
set(LIB_PATH lib)

add_subdirectory(${LIB_PATH}/json)
#add_subdirectory(${LIB_PATH}/cpp-httplib)
add_subdirectory(${LIB_PATH}/sqlite3-cmake)
add_subdirectory(${LIB_PATH}/googletest)

add_library(utils utils.cpp)

#find_library(SQLite3 NAMES sqlite3 PATHS ${LIB_PATH}/sqlite)

include_directories(${LIB_PATH}/json/single_include/nlohmann)
include_directories(${LIB_PATH}/cpp-httplib)
include_directories(${LIB_PATH}/sqlite3-cmake/src)
#include_directories(/usr/local/include)

add_executable(geostats_cvs_parser main.cpp schemas.h)
#add_executable(geostats_cvs_parser_sqlite ${LIB_PATH}/sqlite/sqlite3.c)

#add_library(sqlite_library STATIC ${LIB_PATH}/sqlite/sqlite3.c)

#find_library(SQLITE_LIBRARY sqlite_library ${LIB_PATH}/sqlite)
#find_library(SQLITE_LIBRARY sqlite_library ${LIB_PATH}/sqlite3-cmake)

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
target_link_libraries(geostats_cvs_parser PRIVATE nlohmann_json::nlohmann_json sqlite3 ${CMAKE_DL_LIBS} PUBLIC utils)

#target_link_libraries(geostats_cvs_parser LINK_PUBLIC ${SQLITE_LIBRARY})

#target_include_directories(geostats_cvs_parser PRIVATE ${INCLUDE_DIRS})