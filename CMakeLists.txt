cmake_minimum_required(VERSION 3.0.0)
project(LuxLogger VERSION 0.1.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CXX_FLAGS
        -g
        # -DVALGRIND
        -DCHECK_PTHREAD_RETURN_VALUE
        -D_FILE_OFFSET_BITS=64
        -Wall
        -Wextra
        -Werror
        -Wconversion
        -Wno-unused-parameter
        -Wold-style-cast
        -Woverloaded-virtual
        -Wpointer-arith
        -Wshadow
        -Wwrite-strings
        -march=native
        # -MMD
        -std=c++17
        -rdynamic)
# 32 bit lib
if(CMAKE_BUILD_BITS EQUAL 32)
    list(APPEND CXX_FLAGS "-m32")
endif()

# Clang 
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    list(APPEND CXX_FLAGS "-Wno-null-dereference")
    list(APPEND CXX_FLAGS "-Wno-sign-conversion")
    list(APPEND CXX_FLAGS "-Wno-unused-local-typedef")
    list(APPEND CXX_FLAGS "-Wthread-safety")
    list(REMOVE_ITEM CXX_FLAGS "-rdynamic")
endif()
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR})

string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

set (SRC src/Condition.cc
        src/CountDownLatch.cc
        src/CurrentThread.cc
        src/Exception.cc
        src/FileUtil.cc
        src/LogFile.cc
        src/LogStream.cc
        src/ProcessInfo.cc
        src/Thread.cc
        src/Timestamp.cc
        src/AsyncLogger.cc
        src/Logger.cc)
# Library
add_library(LuxLogger SHARED ${SRC})
target_link_libraries(LuxLogger pthread)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION LuxLogger)

# Examples
add_executable(LuxLoggerExample1 example/example1.cc)
target_link_libraries(LuxLoggerExample1 LuxLogger)
add_executable(LuxLoggerExample2 example/example2.cc)
target_link_libraries(LuxLoggerExample2 LuxLogger)

# Optional
if(NOT BUILD_NO_TEST)
  add_subdirectory(test)
endif()