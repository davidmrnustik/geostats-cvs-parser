cmake_minimum_required(VERSION 3.21)
project(geostats_cvs_parser)

set(CMAKE_CXX_STANDARD 14)

set(JSON_Install OFF CACHE INTERNAL "")

#find_package(nlohmann_json 3.2.0 REQUIRED)

set(LIB_PATH lib)

add_subdirectory(${LIB_PATH}/nlohmann_json)
add_subdirectory(${LIB_PATH}/cpp-httplib)
#add_subdirectory(${LIB_PATH}/sqlite)

#find_library(SQLite3 NAMES sqlite3 PATHS ${LIB_PATH}/sqlite)

include_directories(${LIB_PATH}/nlohmann_json/single_include/nlohmann)
include_directories(${LIB_PATH}/cpp-httplib/httplib.h)
include_directories(${LIB_PATH}/sqlite/sqlite3.h)
#include_directories(/usr/local/include)

add_executable(geostats_cvs_parser main.cpp schemas.h)
#add_executable(geostats_cvs_parser_sqlite ${LIB_PATH}/sqlite/sqlite3.c)

add_library(sqlite_library STATIC ${LIB_PATH}/sqlite/sqlite3.c)

find_library(SQLITE_LIBRARY sqlite_library ${LIB_PATH}/sqlite)
target_link_libraries(geostats_cvs_parser PRIVATE nlohmann_json::nlohmann_json httplib)
target_link_libraries(geostats_cvs_parser LINK_PUBLIC ${SQLITE_LIBRARY})

#target_include_directories(geostats_cvs_parser PRIVATE ${INCLUDE_DIRS})