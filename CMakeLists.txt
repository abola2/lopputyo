cmake_minimum_required(VERSION 3.20)
project(lopputyo CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE PROJECT_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_LIST_DIR}/sources/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/sources/*.h"
)

set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/sources")

message(STATUS "Preparing third-party library 'sqlite3'")

include(FetchContent)

FetchContent_Declare(
    sqlite3
    URL https://sqlite.org/2025/sqlite-amalgamation-3510000.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(sqlite3)

add_library(sqlite3_lib STATIC "${sqlite3_SOURCE_DIR}/sqlite3.c")
set_target_properties(sqlite3_lib PROPERTIES LINKER_LANGUAGE C)
target_include_directories(sqlite3_lib PUBLIC "${sqlite3_SOURCE_DIR}")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_INCLUDE}")

target_link_libraries(${PROJECT_NAME} PRIVATE sqlite3_lib)
