cmake_minimum_required( VERSION 2.8.9 )

project( limepipes CXX)
set( Project_VERSION_MAJOR "0" )
set( Project_VERSION_MINOR "1" )
set( Project_VERSION_PATCH "1" )

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -stdlib=libc++")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # using Intel C++
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # using Visual Studio C++
endif()

set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )

set( OUTPUT_BIN_FOLDER ${CMAKE_BINARY_DIR}/bin )

set( Project_VERSION "${Project_VERSION_MAJOR}.${Project_VERSION_MINOR}.${Project_VERSION_PATCH}")
configure_file(
  "${PROJECT_SOURCE_DIR}/LimePipesConfig.h.in"
  "${PROJECT_BINARY_DIR}/LimePipesConfig.h"
  )

include_directories(
        ${PROJECT_BINARY_DIR}
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/src/model"
        "${CMAKE_SOURCE_DIR}/src/interfaces"
        "${CMAKE_SOURCE_DIR}/src/views"
        "${CMAKE_SOURCE_DIR}/src/app"
        )

enable_testing()

add_subdirectory( src )
#add_subdirectory( tests )
